#include "logger.h"

#include <string>
#include <cmath>

// Hal
#include "hal_timer.h"
#include "hal_uart.h"

// Lib
#include "debugLog.h"
#include "ntlibc.h"

// Msg
#include "msgBroker.h"
#include "actuatorOutputMsg.h"
#include "batteryInfoMsg.h"
#include "ctrlSetpointMsg.h"
#include "imuMsg.h"
#include "pidControlValMsg.h"
#include "wallSensorMsg.h"
#include "vehicleAttitudeMsg.h"
#include "vehiclePositionMsg.h"
#include "parameterManager.h"
#include "wheelOdometryMsg.h"
#include "navStateMsg.h"
#include "trajTripletMsg.h"

static float _log_data[1500][53];

namespace module {

    Logger::Logger() :
        _data_num(0),
        _start_time_ms(0),
        _skip_mod(0),
        _logging(false) {
        setModuleName("Logger");
    }

    void Logger::printHeadder() {
        PRINTF_ASYNC(
            "timestamp,"
            "v_enc,"
            "v_ave,"
            "v_comp,"
            "v_acc,"
            "v_setp,"
            "yawrate,"
            "yawrate_traj,"
            "yawrate_setp,"
            "yaw,"
            "yaw_traj,"
            "yaw_setp,"
            "beta,"
            "beta_setp,"
            "beta_dot,"
            "beta_dot_setp,"
            "x_cor,"
            "y_cor,"
            "x_cor_setp,"
            "y_cor_setp,"
            "a_x,"
            "a_y,"
            "a_setp,"
            "d_la,"
            "d_l,"
            "d_r,"
            "d_ra,"
            "wall_la,"
            "wall_l,"
            "wall_r,"
            "wall_ra,"
            "v_p,"
            "v_i,"
            "v_d,"
            "duty_v,"
            "yawrate_p,"
            "yawrate_i,"
            "yawrate_d,"
            "duty_yaw,"
            "yaw_p,"
            "yaw_i,"
            "wall_p,"
            "wall_i,"
            "wall_d,"
            "diag_p,"
            "voltage,"
            "turn_type,"
            "on_wall_center_time,"
            "not_corner_l_elapsed_time,"
            "not_corner_r_elapsed_time,"
            "in_detect_edge_area,"
            "detected_edge,"
            "three_section_ahead_dist"
            "\n"
        );
    }

    void Logger::print() {

        if(_logging) return;

        printHeadder();

        for(uint32_t i=0; i<_data_num; i++) {
            PRINTF_ASYNC("%f, %f, %f, %f, %f, %f, %f, %f, %f, %f,"
                         "%f, %f, %f, %f, %f, %f, %f, %f, %f, %f,"
                         "%f, %f, %f, %f, %f, %f, %f, %f, %f, %f,"
                         "%f, %f, %f, %f, %f, %f, %f, %f, %f, %f,"
                         "%f, %f, %f, %f, %f, %f, %f, %f, %f, %f,"
                         "%f, %f, %f\n"
                         ,
                         _log_data[i][0],  _log_data[i][1],  _log_data[i][2],  _log_data[i][3],  _log_data[i][4],
                         _log_data[i][5],  _log_data[i][6],  _log_data[i][7],  _log_data[i][8],  _log_data[i][9],
                         _log_data[i][10], _log_data[i][11], _log_data[i][12], _log_data[i][13], _log_data[i][14],
                         _log_data[i][15], _log_data[i][16], _log_data[i][17], _log_data[i][18], _log_data[i][19],
                         _log_data[i][20], _log_data[i][21], _log_data[i][22], _log_data[i][23], _log_data[i][24],
                         _log_data[i][25], _log_data[i][26], _log_data[i][27], _log_data[i][28], _log_data[i][29],
                         _log_data[i][30], _log_data[i][31], _log_data[i][32], _log_data[i][33], _log_data[i][34],
                         _log_data[i][35], _log_data[i][36], _log_data[i][37], _log_data[i][38], _log_data[i][39],
                         _log_data[i][40], _log_data[i][41], _log_data[i][42], _log_data[i][43], _log_data[i][44],
                         _log_data[i][45], _log_data[i][46], _log_data[i][47], _log_data[i][48], _log_data[i][49],
                         _log_data[i][50], _log_data[i][51], _log_data[i][52]
                        );
            hal::waitusec(1300);
        }
    }

    void Logger::printPickleMsg() {
        PRINTF_ASYNC("----- logger pickle msg -----\n");
        hal::feedPickleWithPrintfAsync();
    }

    void Logger::debug() {
        PRINTF_ASYNC("  ----- logger status -----\n");
        PRINTF_ASYNC("  data_num      : %d\n", _data_num);
        PRINTF_ASYNC("  start_time_ms : %d\n", _start_time_ms);
        PRINTF_ASYNC("  skip_mod      : %d\n", _skip_mod);
        PRINTF_ASYNC("  max_data_num  : %d\n", _max_data_num);
        PRINTF_ASYNC("  logging       : %d\n", _logging);
    }


    void Logger::start() {
        _data_num = 0;
        _logging = true;
        _start_time_ms = hal::getElapsedMsec() ;
    }


    void Logger::end() {
        _logging = false;
    }

    void Logger::update3() {
        _skip_mod = ParameterManager::getInstance().logger_skip_mod;

        static uint32_t count = 0;
        count ++;

        if( !(_skip_mod == 1 || _skip_mod == 0)) {
            if( (count % _skip_mod) != 0) return;
        }

        if(_data_num >= _max_data_num) {
            _logging = false;
            _data_num = _max_data_num;
        }

        if(_logging) {
            ActuatorOutputMsg aout_msg;
            BatteryInfoMsg bat_msg;
            CtrlSetpointMsg ctrl_msg;
            ImuMsg imu_msg;
            PidControlValMsg pid_msg;
            WallSensorMsg ws_msg;
            VehicleAttitudeMsg att_msg;
            VehiclePositionMsg pos_msg;
            WheelOdometryMsg wodo_msg;
            NavStateMsg nav_msg;
            TrajTripletMsg traj_msg;

            copyMsg(msg_id::ACTUATOR_OUTPUT, &aout_msg);
            copyMsg(msg_id::BATTERY_INFO, &bat_msg);
            copyMsg(msg_id::CTRL_SETPOINT, &ctrl_msg);
            copyMsg(msg_id::IMU, &imu_msg);
            copyMsg(msg_id::PID_CONTROL_VAL, &pid_msg);
            copyMsg(msg_id::WALL_SENSOR, &ws_msg);
            copyMsg(msg_id::VEHICLE_ATTITUDE, &att_msg);
            copyMsg(msg_id::VEHICLE_POSITION, &pos_msg);
            copyMsg(msg_id::WHEEL_ODOMETRY, &wodo_msg);
            copyMsg(msg_id::NAV_STATE, &nav_msg);
            copyMsg(msg_id::TRAJ_TRIPLET, &traj_msg);

            constexpr float PI = 3.14159265f;
            constexpr float RAD2DEG = 180.0f / PI;
            _log_data[_data_num][0] = (float)(hal::getElapsedMsec() - _start_time_ms)/1000.0f;
            _log_data[_data_num][1] = pos_msg.v_xy_body_enc;
            _log_data[_data_num][2] = pos_msg.v_xy_body_ave;
            _log_data[_data_num][3] = pos_msg.v_xy_body_cmp;
            _log_data[_data_num][4] = pos_msg.v_xy_body_acc;
            _log_data[_data_num][5] = pid_msg.setp_v_xy_body;

            _log_data[_data_num][6] = att_msg.yawrate * RAD2DEG;
            _log_data[_data_num][7] = ctrl_msg.yawrate * RAD2DEG;
            _log_data[_data_num][8] = pid_msg.setp_yawrate * RAD2DEG;


            float ang_diff = ctrl_msg.yaw - att_msg.yaw;

            while(ang_diff >  PI) ang_diff -= 2.0f * PI;

            while(ang_diff < -PI) ang_diff += 2.0f * PI;

            _log_data[_data_num][9] = ang_diff * RAD2DEG;

            _log_data[_data_num][10] = ctrl_msg.yaw * RAD2DEG;
            _log_data[_data_num][11] = pid_msg.setp_yaw * RAD2DEG;

            _log_data[_data_num][12] = att_msg.beta * RAD2DEG;
            _log_data[_data_num][13] = ctrl_msg.beta * RAD2DEG;

            _log_data[_data_num][14] = att_msg.beta_dot * RAD2DEG;
            _log_data[_data_num][15] = ctrl_msg.beta_dot * RAD2DEG;

            _log_data[_data_num][16] = pos_msg.x / 0.09f;
            _log_data[_data_num][17] = pos_msg.y / 0.09f;
            _log_data[_data_num][18] = ctrl_msg.x / 0.09f;
            _log_data[_data_num][19] = ctrl_msg.y / 0.09f;

            _log_data[_data_num][20] = imu_msg.acc_x;
            _log_data[_data_num][21] = imu_msg.acc_y;
            _log_data[_data_num][22] = ctrl_msg.a_xy_body;

            _log_data[_data_num][23] = ws_msg.dist_al;
            _log_data[_data_num][24] = ws_msg.dist_l;
            _log_data[_data_num][25] = ws_msg.dist_r;
            _log_data[_data_num][26] = ws_msg.dist_ar;
            _log_data[_data_num][27] = (float)ws_msg.ahead_l;
            _log_data[_data_num][28] = (float)ws_msg.left;
            _log_data[_data_num][29] = (float)ws_msg.right;
            _log_data[_data_num][30] = (float)ws_msg.ahead_r;

            _log_data[_data_num][31] = pid_msg.v_p;
            _log_data[_data_num][32] = pid_msg.v_i;
            _log_data[_data_num][33] = pid_msg.v_d;
            _log_data[_data_num][34] = aout_msg.duty_r_v;

            _log_data[_data_num][35] = pid_msg.yawrate_p;
            _log_data[_data_num][36] = pid_msg.yawrate_i;
            _log_data[_data_num][37] = pid_msg.yawrate_d;
            _log_data[_data_num][38] = aout_msg.duty_r_yaw;

            float v_now = pos_msg.v_xy_body_for_ctrl;

            if(v_now < 0.05f) v_now = 0.05f;

            _log_data[_data_num][39] = v_now * pid_msg.yaw_p * RAD2DEG;
            _log_data[_data_num][40] = v_now * pid_msg.yaw_i * RAD2DEG;
            _log_data[_data_num][41] = v_now * pid_msg.wall_p * RAD2DEG;
            _log_data[_data_num][42] = v_now * pid_msg.wall_i * RAD2DEG;
            _log_data[_data_num][43] = v_now * pid_msg.wall_d * RAD2DEG;
            _log_data[_data_num][44] = v_now * pid_msg.diag_p * RAD2DEG;

            _log_data[_data_num][45] = bat_msg.voltage;

            _log_data[_data_num][46] = (uint8_t)ctrl_msg.turn_type;

            _log_data[_data_num][47] = ws_msg.on_wall_center_time;
            _log_data[_data_num][48] = ws_msg.not_corner_l_elapsed_time;
            _log_data[_data_num][49] = ws_msg.not_corner_r_elapsed_time;
            _log_data[_data_num][50] = ctrl_msg.in_detect_edge_area * (int8_t)traj_msg.turn_dir_next;
            _log_data[_data_num][51] = ctrl_msg.detected_edge;
            _log_data[_data_num][52] = 0.09f * 3.0f - pos_msg.y;

            _data_num++;
        }

    }

    int usrcmd_logger(int argc, char** argv) {
        if (ntlibc_strcmp(argv[1], "help") == 0) {
            PRINTF_ASYNC("  status :\r\n");
            PRINTF_ASYNC("  start  :\r\n");
            PRINTF_ASYNC("  end    :\r\n");
            PRINTF_ASYNC("  print  :\r\n");
            PRINTF_ASYNC("  pickle :\r\n");
            PRINTF_ASYNC("  test   :\r\n");
            return 0;
        }

        if (ntlibc_strcmp(argv[1], "status") == 0) {
            Logger::getInstance().debug();
            return 0;
        }

        if (ntlibc_strcmp(argv[1], "start") == 0) {
            if(argc == 2) {
                Logger::getInstance().start();
                return 0;
            }
            else if(argc == 3) {
                std::string num_str(argv[2]);
                int32_t num = std::stoi(num_str);

                ParameterManager::getInstance().write<uint8_t>("logger_skip_mod", (uint8_t)num);
                Logger::getInstance().start();
                return 0;
            }
        }

        if (ntlibc_strcmp(argv[1], "end") == 0) {
            Logger::getInstance().end();
            return 0;
        }

        if (ntlibc_strcmp(argv[1], "print") == 0) {
            PRINTF_ASYNC("------------------------------------------\n");
            Logger::getInstance().print();
            return 0;
        }

        if (ntlibc_strcmp(argv[1], "pickle") == 0) {
            Logger::getInstance().printPickleMsg();
            return 0;
        }


        if (ntlibc_strcmp(argv[1], "test") == 0) {
            {
                uint32_t start_time = hal::getElapsedMsec();
                PRINTF_ASYNC("  PRINT_PICKLE x 100 times| %f, %f, %f, %f, %f, %f, %f, %f \n", 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f);

                for(uint16_t i=0; i<100; i++) {
                    PRINTF_PICKLE("  %f, %f, %f, %f, %f, %f, %f, %f\n", 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f);
                }

                uint32_t elapsed_time = hal::getElapsedMsec() - start_time;
                PRINTF_ASYNC("  elapsed : %d [ms]\n", elapsed_time);
                Logger::getInstance().printPickleMsg();
            }
            PRINTF_ASYNC("---------------\n");
            {
                uint32_t start_time = hal::getElapsedMsec();
                PRINTF_ASYNC("  PRINTF_ASYNC x 100 times| %f, %f, %f, %f, %f, %f, %f, %f \n", 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f);

                for(uint16_t i=0; i<100; i++) {
                    PRINTF_ASYNC("  %f, %f, %f, %f, %f, %f, %f, %f\n", 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f);
                }

                uint32_t elapsed_time = hal::getElapsedMsec() - start_time;
                PRINTF_ASYNC("  elapsed : %d [ms]\n", elapsed_time);
            }
            return 0;
        }

        PRINTF_ASYNC("  Unknown sub command\r\n");
        return -1;

    }

}

