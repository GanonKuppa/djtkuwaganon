#include "shell.h"

#include <string.h>
#include <stdint.h>

// Lib/ntshell
#include "ntopt.h"
#include "ntlibc.h"
#include "ntshell.h"
#include "text_history.h"


#include "debugLog.h"

// Hal
#include "hal_uart.h"
#include "hal_timerInterrupt.h"
#include "hal_timer.h"
#include "hal_flashRom.h"

// Module
#include "baseModule.h"
#include "batteryMonitor.h"
#include "controlMixer.h"
#include "heater.h"
#include "imuDriver.h"
#include "ledController.h"
#include "logger.h"
#include "navigator.h"
#include "parameterManager.h"
#include "positionEstimator.h"
#include "powerTransmission.h"
#include "pseudoDial.h"
#include "shell.h"
#include "suction.h"
#include "trajectoryCommander.h"
#include "trajectoryInitializer.h"
#include "wallSensor.h"
#include "wheelOdometry.h"
#include "truthMaker.h"
#include "gamepad.h"
#include "seManager.h"
#include "runAnalizer.h"



static int usrcmd_ntopt_callback(int argc, char** argv, void* extobj);
static int user_callback(const char* text, void* extobj);
static int serial_read(char* buf, int cnt, void* extobj);
static int serial_write(const char* buf, int cnt, void* extobj);
static void readHistoryFromFlash(ntshell_t* nts);
static void writeHistory2Flash(ntshell_t* nts);



static int usrcmd_help(int argc, char** argv);
static int usrcmd_info(int argc, char** argv);
static int usrcmd_top(int argc, char** argv);
static int usrcmd_calcTest(int argc, char** argv);
static int usrcmd_loggerPrint(int argc, char** argv);
static int usrcmd_loggerPickle(int argc, char** argv);
static int usrcmd_batteryStatus(int argc, char** argv);

typedef int (*USRCMDFUNC)(int argc, char** argv);

typedef struct {
    const char* cmd;
    const char* desc;
    USRCMDFUNC func;
} cmd_table_t;



static const cmd_table_t cmdlist[] = {
    { "help", "help command.", usrcmd_help },
    { "info", "system info.", usrcmd_info },
    { "top", "top command.", usrcmd_top },
    { "calcTest", "calcTest command.", usrcmd_calcTest },
    { "l", "logger print command.", usrcmd_loggerPrint },
    { "lp", "logger pickle command.", usrcmd_loggerPickle },
    { "b", "battery status command.", usrcmd_batteryStatus },
    { "batteryMonitor", "BatteryMonitor Module.", module::usrcmd_batteryMonitor },
    { "battery", "alias of batteryMonitor command.", module::usrcmd_batteryMonitor },
    { "controlMixer", "ControlMixer.", module::usrcmd_controlMixer },
    { "heater", "Heater Module.", module::usrcmd_heater },
    { "imuDriver", "ImuDriver Module.", module::usrcmd_imuDriver },
    { "imu", "alias of imuDriver command.", module::usrcmd_imuDriver },
    { "ledController", "LedController Module.", module::usrcmd_ledController },
    { "led", "ailias of ledController command.", module::usrcmd_ledController },
    { "logger", "Logger Module.", module::usrcmd_logger },
    { "navigator", "Navigator Module.", module::usrcmd_navigator },
    { "paramManager", "ParamManager Module.", module::usrcmd_parameterManager },
    { "param", "alias of paramManager command.", module::usrcmd_parameterManager },
    { "positionEstimator", "PositionEstimator Module.", module::usrcmd_positionEstimator },
    { "position", "alias of positionEstimator command.", module::usrcmd_positionEstimator },
    { "powerTransmission", "PowerTransmission Module.", module::usrcmd_powerTransmission },
    { "power", "alias of powerTransmission command.", module::usrcmd_powerTransmission },
    { "pseudoDial", "pseudoDial Module.", module::usrcmd_pseudoDial },
    { "shell", "shell Module.", module::usrcmd_shell },
    { "suction", "Suction Module.", module::usrcmd_suction },
    { "trajectoryCommander", "TrajectoryCommander Module.", module::usrcmd_trajectoryCommander },
    { "trajectoryInitializer", "TrajectoryInitializer Module.", module::usrcmd_trajectoryInitializer },
    { "wallSensor", "WallSensor Module.", module::usrcmd_wallSensor },
    { "wheelOdometry", "WheelOdometry Module.", module::usrcmd_wheelOdometry },
    { "wheel", "alias of wheelOdometry command.", module::usrcmd_wheelOdometry },
    { "truthMaker", "TruthMaker Module.", module::usrcmd_truthMaker },
    { "gamepad", "Gamepad Module.", module::usrcmd_gamepad },
    { "seManager", "seManager Module.", module::usrcmd_seManager },
    { "runAnalizer", "runAnalizer Module.", module::usrcmd_runAnalizer }
};

int serial_write(const char* buf, int cnt, void* extobj) {
    hal::putnbyteUart1((uint8_t*)buf, cnt);
    return cnt;
}

int usrcmd_ntopt_callback(int argc, char** argv, void* extobj) {
    if (argc == 0) {
        return 0;
    }

    const cmd_table_t* p = &cmdlist[0];

    for (uint16_t i = 0; i < sizeof(cmdlist) / sizeof(cmdlist[0]); i++) {
        if (ntlibc_strcmp((const char*)argv[0], p->cmd) == 0) {
            return p->func(argc, argv);
        }

        p++;
    }

    PRINTF_ASYNC("Unknown command.\r\n");
    return -1;
}

int user_callback(const char* text, void* extobj) {
    int parse_ret = ntopt_parse(text, usrcmd_ntopt_callback, 0);
    if(parse_ret == 0) writeHistory2Flash(module::Shell::getInstance().getNtsPtr());
    return 0;
}


int serial_read(char* buf, int cnt, void* extobj) {

    if(!hal::isEmptyRecvBufUart1()) {
        uint16_t recvBufsize = hal::getRecvBufUart1size();
        uint16_t read_size = cnt;

        if(cnt > recvBufsize) {
            read_size = recvBufsize;
        }

        bool rtn = hal::readnbyteUart1((uint8_t*)buf, read_size);

        if(rtn == false) {
            return 0;
        }
        else {
            return read_size;
        }
    }
    else {
        return 0;
    }
}


void readHistoryFromFlash(ntshell_t* nts) {
    constexpr uint16_t WRITE_TARGET_BLOCK = 768;
    constexpr uint16_t START_INDEX = WRITE_TARGET_BLOCK * hal::FLASH_BLOCK_BYTE_SIZE;
    constexpr uint16_t BLOCK_NUM = 16;
    constexpr uint32_t LEN = hal::FLASH_BLOCK_BYTE_SIZE * BLOCK_NUM + 8; // nts->history???????????????
    hal::readFlashRom(START_INDEX, &(nts->history.history[0]), LEN);
}

void writeHistory2Flash(ntshell_t* nts) {
    constexpr uint16_t WRITE_TARGET_BLOCK = 768;
    constexpr uint16_t START_INDEX = WRITE_TARGET_BLOCK * hal::FLASH_BLOCK_BYTE_SIZE;
    constexpr uint16_t BLOCK_NUM = 17; // nts->history????????????????????????????????????
    constexpr uint32_t LEN = hal::FLASH_BLOCK_BYTE_SIZE;

    uint8_t* write_val = (uint8_t*)(&(nts->history.history[0]));

    for(uint8_t i=0; i<BLOCK_NUM; i++) {
        uint32_t index = START_INDEX + i*LEN;

        while(1) {
            if(hal::eraseCheckFlashRom(index, LEN) == false) {
                hal::eraseFlashRom(index);
            };

            hal::writeFlashRom(index, &write_val[i*LEN], LEN);

            uint8_t read_val[LEN];

            hal::readFlashRom(index, &read_val[0], LEN);

            bool check_result = true;

            for(uint8_t j=0; j<LEN; j++) {
                if(read_val[j] != write_val[i*LEN+j]) {
                    check_result = false;
                }
            }

            if(check_result) break;
        }
    }
}


int usrcmd_help(int argc, char** argv) {
    const cmd_table_t* p = &cmdlist[0];

    for (uint16_t i = 0; i < sizeof(cmdlist) / sizeof(cmdlist[0]); i++) {
        PRINTF_ASYNC("  ");
        PRINTF_ASYNC(p->cmd);
        int command_len_max = 24;
        int space_num = command_len_max - strlen(p->cmd);

        if(space_num > 0) {
            for(int i = 0; i < space_num; i++) {
                PRINTF_ASYNC(" ");
            }
        }

        PRINTF_ASYNC(": ");
        PRINTF_ASYNC(p->desc);
        PRINTF_ASYNC("\r\n");
        p++;
        hal::waitmsec(10);
    }

    return 0;
}

int usrcmd_info(int argc, char** argv) {
    if (argc != 2) {
        PRINTF_ASYNC("info sys\r\n");
        PRINTF_ASYNC("info ver\r\n");
        return 0;
    }

    if (ntlibc_strcmp(argv[1], "sys") == 0) {
        PRINTF_ASYNC("  ");
        PRINTF_ASYNC("djtkuwaganon\r\n");
        return 0;
    }

    if (ntlibc_strcmp(argv[1], "ver") == 0) {
        PRINTF_ASYNC("  ");
        PRINTF_ASYNC("Version 0.0.1\r\n");
        return 0;
    }

    PRINTF_ASYNC("  ");
    PRINTF_ASYNC("Unknown sub command\r\n");
    return -1;
}

int usrcmd_top(int argc, char** argv) {
    float slot0_time = hal::getSlot0Time();
    float slot1_time = hal::getSlot1Time();
    float slot2_time = hal::getSlot2Time();
    float slot3_time = hal::getSlot3Time();
    PRINTF_ASYNC("\n");
    PRINTF_ASYNC("  --- timerInterrupt0 Slot Time 0, 1, 2, 3\n");
    PRINTF_ASYNC("      total = %6.2f[us]\n",slot0_time + slot1_time + slot2_time + slot3_time);
    PRINTF_ASYNC("      %6.2f[us], %6.2f[us], %6.2f[us], %6.2f[us]\n",slot0_time, slot1_time, slot2_time, slot3_time);

    PRINTF_ASYNC("\n");

    PRINTF_ASYNC("  --- Modules Time --- \n");
    PRINTF_ASYNC("      update0   , update1   , update2   , update3   ,updateEvery, updateInMainLoop\n");

    module::BatteryMonitor::getInstance().printCycleTime();
    hal::waitmsec(10);
    module::ControlMixer::getInstance().printCycleTime();
    hal::waitmsec(10);
    module::Heater::getInstance().printCycleTime();
    hal::waitmsec(10);
    module::ImuDriver::getInstance().printCycleTime();
    hal::waitmsec(10);
    module::LedController::getInstance().printCycleTime();
    hal::waitmsec(10);
    module::Logger::getInstance().printCycleTime();
    hal::waitmsec(10);
    module::Navigator::getInstance().printCycleTime();
    hal::waitmsec(10);
    module::ParameterManager::getInstance().printCycleTime();
    hal::waitmsec(10);
    module::PositionEstimator::getInstance().printCycleTime();
    hal::waitmsec(10);
    module::PowerTransmission::getInstance().printCycleTime();
    hal::waitmsec(10);
    module::PseudoDial::getInstance().printCycleTime();
    hal::waitmsec(10);
    module::Shell::getInstance().printCycleTime();
    hal::waitmsec(10);
    module::Suction::getInstance().printCycleTime();
    hal::waitmsec(10);
    module::TrajectoryCommander::getInstance().printCycleTime();
    hal::waitmsec(10);
    module::TrajectoryInitializer::getInstance().printCycleTime();
    hal::waitmsec(10);
    module::WallSensor::getInstance().printCycleTime();
    hal::waitmsec(10);
    module::WheelOdometry::getInstance().printCycleTime();
    hal::waitmsec(10);
    module::TruthMaker::getInstance().printCycleTime();
    hal::waitmsec(10);
    module::Gamepad::getInstance().printCycleTime();
    hal::waitmsec(10);
    module::SeManager::getInstance().printCycleTime();
    hal::waitmsec(10);
    module::RunAnalizer::getInstance().printCycleTime();
    hal::waitmsec(10);


    return 0;
}

int usrcmd_calcTest(int argc, char** argv){
    hal::stopTimerInterrupt0();
    {
        uint32_t usec_start = hal::getElapsedUsec();
        double DELTA_T = 0.001;
        double SUM = 0.0;
        for(uint32_t i=0;i<1000;i++){
            SUM += DELTA_T;
        }
        uint32_t usec_end = hal::getElapsedUsec();
        PRINTF_ASYNC("--DADD x 1000 %d us | SUM = %f\n",usec_end - usec_start, SUM);
    }

    {
        uint32_t usec_start = hal::getElapsedUsec();
        double DELTA_T = 0.001;
        double SUM = 1.0;
        for(uint32_t i=0;i<1000;i++){
            SUM *= 1.01;
        }
        uint32_t usec_end = hal::getElapsedUsec();
        PRINTF_ASYNC("--DMUL x 1000 %d us | SUM = %f\n",usec_end - usec_start, SUM);
    }

    {
        uint32_t usec_start = hal::getElapsedUsec();
        double DELTA_T = 0.001;
        double SUM = 1.0;
        for(uint32_t i=0;i<1000;i++){
            SUM /= 1.01;
        }
        uint32_t usec_end = hal::getElapsedUsec();
        PRINTF_ASYNC("--DDIV x 1000 %d us | SUM = %f\n",usec_end - usec_start, SUM);
    }

    {
        uint32_t usec_start = hal::getElapsedUsec();
        float DELTA_T = 0.001f;
        float SUM = 0.0f;
        for(uint32_t i=0;i<1000;i++){
            SUM += DELTA_T;
        }
        uint32_t usec_end = hal::getElapsedUsec();
        PRINTF_ASYNC("--FADD x 1000 %d us | SUM = %f\n",usec_end - usec_start, SUM);
    }

    {
        uint32_t usec_start = hal::getElapsedUsec();
        float DELTA_T = 0.001f;
        float SUM = 1.0f;
        for(uint32_t i=0;i<1000;i++){
            SUM *= 1.01f;
        }
        uint32_t usec_end = hal::getElapsedUsec();
        PRINTF_ASYNC("--FMUL x 1000 %d us | SUM = %f\n",usec_end - usec_start, SUM);
    }

    {
        uint32_t usec_start = hal::getElapsedUsec();
        float DELTA_T = 0.001f;
        float SUM = 1.0f;
        for(uint32_t i=0;i<1000;i++){
            SUM /= 1.01f;
        }
        uint32_t usec_end = hal::getElapsedUsec();
        PRINTF_ASYNC("--FDIV x 1000 %d us | SUM = %f\n",usec_end - usec_start, SUM);
    }

    hal::startTimerInterrupt0();
    return 0;
}

static int usrcmd_loggerPrint(int argc, char** argv){
    char *argv_l[2] = {"logger", "print"};
    module::usrcmd_logger(2, (char**)(&argv_l));
    return 0;
}

static int usrcmd_loggerPickle(int argc, char** argv){
    char *argv_lp[2] = {"logger", "pickle"};
    module::usrcmd_logger(2, (char**)(&argv_lp));
    return 0;
}

static int usrcmd_batteryStatus(int argc, char** argv){
    char *argv_bs[2] = {"battery", "status"};
    module::usrcmd_batteryMonitor(2, (char**)(&argv_bs));
    return 0;
}



namespace module {


    Shell::Shell() {
        setModuleName("Shell");

        void* extobj = 0;
        ntshell_init(&nts, serial_read, serial_write, user_callback, extobj);
        readHistoryFromFlash(&nts);
        ntshell_set_prompt(&nts, "djtkuwaganon>");
    };

    void Shell::updateEvery() {
        hal::sendDataUart1();
        hal::recvDataUart1();
        hal::sendDataUart1();
    }
    void Shell::update0() {
        hal::sendDataUart1();
        hal::recvDataUart1();
        hal::sendDataUart1();
    }

    void Shell::update1() {
        hal::sendDataUart1();
        hal::recvDataUart1();
        hal::sendDataUart1();
    }

    void Shell::update2() {
        hal::sendDataUart1();
        hal::recvDataUart1();
        hal::sendDataUart1();
    }

    void Shell::update3() {
        hal::sendDataUart1();
        hal::recvDataUart1();
        hal::sendDataUart1();
    }

    void Shell::updateInMainLoop() {
        ntshell_execute(&nts);
    }


    int usrcmd_shell(int argc, char** argv) {
        return 0;
    }
}






