#include <PeripheralDriverLayer/pd_clock.h>
#include <PeripheralDriverLayer/pd_pwm.h>
#include <stdint.h>
#include <cmath>
#include <cfloat>
#include <algorithm>
#include "iodefine.h"


//49ピン PC3 MOTOR_L_PWM2 MTIOC4B //GTIOC1B-D
//50ピン PC2 MOTOR_L_PWM1 MTIOC4D //GTIOC2B-D
//51ピン PC1 MOTOR_R_PWM1 MTIOC3A
//52ピン PC0 MOTRO_R_PWM2 MTIOC3C

//68ピン PA2 SUC_MOTOR_PWM MTIOC7A
//69ピン PA1 HEATER_PWM MTIOC7B/MTIOC0B/GTIOC2A-C/TIOCB0

namespace peripheral_driver {
    static float dutyPA1MTU0B;
    static float dutyPC3GPTA1;
    static float dutyPC2GPTA2;
    static float dutyPC1MTU3A;
    static float dutyPC0MTU3C;
    static float dutyPA2MTU7A;
    static float dutyP23GPTA0;
    static float dutyP24MTU4A;

    static constexpr uint16_t FREQ_COUNT = 350;

    void initPA1MTU0B(){
        SYSTEM.PRCR.WORD = 0xA502;
        SYSTEM.MSTPCRA.BIT.MSTPA9 = 0; //MTUモジュールON
        SYSTEM.PRCR.WORD = 0xA500;

        MPC.PWPR.BIT.B0WI = 0;
        MPC.PWPR.BIT.PFSWE = 1;
        MPC.PA1PFS.BIT.PSEL = 1; //MTIOC0B
        MPC.PWPR.BYTE = 0x80;

        PORTA.PMR.BIT.B1 = 1;

        MTU.TSTRA.BIT.CST0 = 0;
        MTU0.TCR.BIT.TPSC = 0; //PCLKA/1
        MTU0.TCR.BIT.CCLR = 1; //PWM TGRAのコンペアマッチでTCNTクリア


        MTU0.TIORH.BIT.IOB = 5; //初期出力1 コンペアマッチ0出力
        MTU0.TGRA = FREQ_COUNT;
        MTU0.TGRB = 1;
        MTU0.TGRC = FREQ_COUNT;
        MTU0.TGRD = 1;
        MTU0.TMDR1.BIT.MD = 3; //PWM2
        MTU0.TMDR1.BIT.BFA = 1;   //バッファーモードに設定
        MTU0.TMDR1.BIT.BFB = 1;
        setDutyPA1MTU0B(0.0f);
    }

    void initPC3GPTA1(){
        SYSTEM.PRCR.WORD = 0xA502;
        SYSTEM.MSTPCRA.BIT.MSTPA7 = 0; //GPTAモジュールON
        SYSTEM.PRCR.WORD = 0xA500;

        PORTC.PMR.BIT.B3 = 0;

        MPC.PWPR.BIT.B0WI = 0;
        MPC.PWPR.BIT.PFSWE = 1;
        MPC.PC3PFS.BIT.PSEL = 0b011110; //GTIOC1B
        MPC.PWPR.BYTE = 0x80;

        GPT.GTSTR.BIT.CST1 = 0;
        GPT1.GTIOR.BIT.GTIOB = 0b011001; // 初期出力H 周期の終わりでH出力 コンペアマッチでL
        GPT1.GTONCR.BIT.OBE = 1;
        GPT1.GTPR = FREQ_COUNT;
        GPT1.GTCCRB = 1;
        setDutyPC3GPTA1(0.0f);
    }

    void initPC2GPTA2(){
        SYSTEM.PRCR.WORD = 0xA502;
        SYSTEM.MSTPCRA.BIT.MSTPA7 = 0; //GPTAモジュールON
        SYSTEM.PRCR.WORD = 0xA500;

        PORTC.PMR.BIT.B2 = 0;

        MPC.PWPR.BIT.B0WI = 0;
        MPC.PWPR.BIT.PFSWE = 1;
        MPC.PC2PFS.BIT.PSEL = 0b011110; //GTIOC2B
        MPC.PWPR.BYTE = 0x80;

        GPT.GTSTR.BIT.CST2 = 0;
        GPT2.GTIOR.BIT.GTIOB = 0b011001; // 初期出力H 周期の終わりでH出力 コンペアマッチでL
        GPT2.GTONCR.BIT.OBE = 1;
        GPT2.GTPR = FREQ_COUNT;
        GPT2.GTCCRB = 1;
        setDutyPC2GPTA2(0.0f);
    }

    void initPC1MTU3A(){
        SYSTEM.PRCR.WORD = 0xA502;
        SYSTEM.MSTPCRA.BIT.MSTPA9 = 0; //MTUモジュールON
        SYSTEM.PRCR.WORD = 0xA500;
        
        PORTC.PMR.BIT.B1 = 0;

        MPC.PWPR.BIT.B0WI = 0;
        MPC.PWPR.BIT.PFSWE = 1;
        MPC.PC1PFS.BIT.PSEL = 1; //MTIOC3A
        MPC.PWPR.BYTE = 0x80;

        MTU.TSTRA.BIT.CST3 = 0;
        MTU3.TCR.BIT.TPSC = 0; //PCLKA/1
        MTU3.TCR.BIT.CCLR = 1; //PWM TGRAのコンペアマッチでTCNTクリア
        MTU3.TIORH.BIT.IOA = 6; //初期出力1 コンペアマッチ1出力
        MTU3.TIORH.BIT.IOB = 5; //初期出力1 コンペアマッチ0出力

        MTU3.TGRA = FREQ_COUNT;
        MTU3.TGRB = 1;
        MTU3.TMDR1.BIT.MD = 2; //PWMモード1

        setDutyPC1MTU3A(0.0f);
    }
    
    void initPC0MTU3C(){
        SYSTEM.PRCR.WORD = 0xA502;
        SYSTEM.MSTPCRA.BIT.MSTPA9 = 0; //MTUモジュールON
        SYSTEM.PRCR.WORD = 0xA500;

        PORTC.PMR.BIT.B0 = 0;        

        MPC.PWPR.BIT.B0WI = 0;
        MPC.PWPR.BIT.PFSWE = 1;
        MPC.PC0PFS.BIT.PSEL = 1; //MTIOC3C
        MPC.PWPR.BYTE = 0x80;


        MTU.TSTRA.BIT.CST3 = 0;
        MTU3.TCR.BIT.TPSC = 0; //PCLKA/1
        MTU3.TCR.BIT.CCLR = 1; //PWM TGRAのコンペアマッチでTCNTクリア
        MTU3.TIORL.BIT.IOC = 6; //初期出力1 コンペアマッチ0出力
        MTU3.TIORL.BIT.IOD = 5; //初期出力1 コンペアマッチ0出力

        MTU3.TGRC = FREQ_COUNT;
        MTU3.TGRD = 1;
        MTU3.TMDR1.BIT.MD = 2; //PWMモード1

        setDutyPC0MTU3C(0.0f);
    }

    void initPA2MTU7A(){
        SYSTEM.PRCR.WORD = 0xA502;
        SYSTEM.MSTPCRA.BIT.MSTPA9 = 0; //MTUモジュールON
        SYSTEM.PRCR.WORD = 0xA500;

        MPC.PWPR.BIT.B0WI = 0;
        MPC.PWPR.BIT.PFSWE = 1;
        MPC.PA2PFS.BIT.PSEL = 0b001000; //MTIOC7A
        MPC.PWPR.BYTE = 0x80;

        PORTA.PMR.BIT.B2 = 1;

        MTU.TSTRB.BIT.CST7 = 0;
        MTU.TOERB.BIT.OE7A = 1; //MTU出力端子を出力許可する

        MTU7.TCR.BIT.TPSC = 0; //PCLKA/1
        MTU7.TCR.BIT.CCLR = 1; //PWM TGRAのコンペアマッチでTCNTクリア TGRDは6
        MTU7.TIORH.BIT.IOA = 6; //初期出力1 コンペアマッチ1出力
        MTU7.TIORH.BIT.IOB = 5; //初期出力1 コンペアマッチ0出力
        MTU7.TGRA = FREQ_COUNT;
        MTU7.TGRB = 1;
        MTU7.TGRC = FREQ_COUNT;
        MTU7.TGRD = 1;
        MTU7.TMDR1.BIT.MD = 2; //PWM1
        MTU7.TMDR1.BIT.BFA = 1;   //バッファーモードに設定
        MTU7.TMDR1.BIT.BFB = 1; //バッファーモードに設定

        setDutyPA2MTU7A(0.0f);
    }

    void initP23GPTA0(){
        SYSTEM.PRCR.WORD = 0xA502;
        SYSTEM.MSTPCRA.BIT.MSTPA7 = 0; //GPTAモジュールON
        SYSTEM.PRCR.WORD = 0xA500;

        POE3.POECR3.BIT.GPT0ABZE = 0;

        PORT2.PMR.BIT.B3 = 0;

        MPC.PWPR.BIT.B0WI = 0;
        MPC.PWPR.BIT.PFSWE = 1;
        MPC.P23PFS.BIT.PSEL = 0b011110; //GTIOC0A
        MPC.PWPR.BYTE = 0x80;        

        GPT.GTSTR.BIT.CST0 = 0;
        GPT0.GTIOR.BIT.GTIOA = 0b011001; // 初期出力H 周期の終わりでH出力 コンペアマッチでL
        GPT0.GTONCR.BIT.OAE = 1;
        GPT0.GTPR = FREQ_COUNT;
        GPT0.GTCCRA = 1;
        setDutyP23GPTA0(0.0f);
    }

    void initP24MTU4A(){
        SYSTEM.PRCR.WORD = 0xA502;
        SYSTEM.MSTPCRA.BIT.MSTPA9 = 0; //MTUモジュールON
        SYSTEM.PRCR.WORD = 0xA500;

        POE3.POECR2.BIT.MTU4ACZE = 0;

        PORT2.PMR.BIT.B4 = 0;
        MPC.PWPR.BIT.B0WI = 0;
        MPC.PWPR.BIT.PFSWE = 1;
        MPC.P24PFS.BIT.PSEL = 0b000001; //MTIOC4A
        MPC.PWPR.BYTE = 0x80;        
        
        
        MTU.TSTRA.BIT.CST4 = 0;
        MTU.TOERA.BIT.OE4A = 1; //MTU出力端子を出力許可する

        MTU4.TCR.BIT.TPSC = 0; //PCLKA/1
        MTU4.TCR.BIT.CCLR = 1; //PWM TGRAのコンペアマッチでTCNTクリア TGRDは6
        MTU4.TIORH.BIT.IOA = 6; //初期出力1 コンペアマッチ1出力
        MTU4.TIORH.BIT.IOB = 5; //初期出力1 コンペアマッチ0出力        
        MTU4.TGRA = FREQ_COUNT;
        MTU4.TGRB = 1;
        MTU4.TGRC = FREQ_COUNT;
        MTU4.TGRD = 1;
        MTU4.TMDR1.BIT.MD = 2; //PWMモード1
        MTU4.TMDR1.BIT.BFA = 1;   //バッファーモードに設定
        MTU4.TMDR1.BIT.BFB = 1; //バッファーモードに設定

        setDutyP24MTU4A(0.0f);
    }


    void setDutyPA1MTU0B(float duty){
        duty = std::clamp<float>(duty, 0.0f, 1.0f);
        dutyPA1MTU0B = duty;

        if (std::fabs(duty) < FLT_EPSILON) {
            MTU.TSTRA.BIT.CST0 = 0;
            PORTA.PMR.BIT.B1 = 0;
            PORTA.PDR.BIT.B1 = 1;
            PORTA.PODR.BIT.B1 = 0;
        }
        else if(duty >= 0.9999f) {
            MTU.TSTRA.BIT.CST0 = 0;
            PORTA.PMR.BIT.B1 = 0;
            PORTA.PDR.BIT.B1 = 1;
            PORTA.PODR.BIT.B1 = 1;
        }
        else {
            PORTA.PMR.BIT.B1= 1;
            MTU0.TGRD = (uint16_t) (MTU0.TGRC * duty);
        }

        MTU.TSTRA.BIT.CST0 = 1;
    }

    void setDutyPC3GPTA1(float duty){
        duty = std::clamp<float>(duty, 0.0f, 1.0f);
        dutyPC3GPTA1 = duty;

        if (std::fabs(duty) < FLT_EPSILON) {
            GPT.GTSTR.BIT.CST1 = 0;
            PORTC.PMR.BIT.B3 = 0;
            PORTC.PDR.BIT.B3 = 1;
            PORTC.PODR.BIT.B3 = 0;
        }
        else if(duty >= 0.9999f) {
            GPT.GTSTR.BIT.CST1 = 0;
            PORTC.PMR.BIT.B3 = 0;
            PORTC.PDR.BIT.B3 = 1;
            PORTC.PODR.BIT.B3 = 1;
        }
        else {
            PORTC.PMR.BIT.B3 = 1;
            GPT1.GTCCRB = (uint16_t) (GPT1.GTPR * duty);
        }

        GPT.GTSTR.BIT.CST1 = 1;    
    }

    void setDutyPC2GPTA2(float duty){
        duty = std::clamp<float>(duty, 0.0f, 1.0f);
        dutyPC2GPTA2 = duty;

        if (std::fabs(duty) < FLT_EPSILON) {
            GPT.GTSTR.BIT.CST2 = 0;
            PORTC.PMR.BIT.B2 = 0;
            PORTC.PDR.BIT.B2 = 1;
            PORTC.PODR.BIT.B2 = 0;
        }
        else if(duty >= 0.9999f) {
            GPT.GTSTR.BIT.CST2 = 0;
            PORTC.PMR.BIT.B2 = 0;
            PORTC.PDR.BIT.B2 = 1;
            PORTC.PODR.BIT.B2 = 1;
        }
        else {
            PORTC.PMR.BIT.B2 = 1;
            GPT2.GTCCRB = (uint16_t) (GPT2.GTPR * duty);
        }

        GPT.GTSTR.BIT.CST2 = 1;
    }

    void setDutyPC1MTU3A(float duty){
        duty = std::clamp<float>(duty, 0.0f, 1.0f);
        dutyPC1MTU3A = duty;

        if (std::fabs(duty) < FLT_EPSILON) {
            MTU.TSTRA.BIT.CST3 = 0;
            PORTC.PMR.BIT.B1 = 0;
            PORTC.PDR.BIT.B1 = 1;
            PORTC.PODR.BIT.B1 = 0;
        }
        else if(duty >= 0.9999f) {
            MTU.TSTRA.BIT.CST3 = 0;
            PORTC.PMR.BIT.B1 = 0;
            PORTC.PDR.BIT.B1 = 1;
            PORTC.PODR.BIT.B1 = 1;
        }
        else {
            PORTC.PMR.BIT.B1 = 1;
            MTU3.TGRB = (uint16_t) (MTU3.TGRA * duty);
        }

        MTU.TSTRA.BIT.CST3 = 1;
    }

    void setDutyPC0MTU3C(float duty){
        duty = std::clamp<float>(duty, 0.0f, 1.0f);
        dutyPC0MTU3C = duty;

        if (std::fabs(duty) < FLT_EPSILON) {
            MTU.TSTRA.BIT.CST3 = 0;
            PORTC.PMR.BIT.B0 = 0;
            PORTC.PDR.BIT.B0 = 1;
            PORTC.PODR.BIT.B0 = 0;
        }
        else if(duty >= 0.9999f) {
            MTU.TSTRA.BIT.CST3 = 0;
            PORTC.PMR.BIT.B0 = 0;
            PORTC.PDR.BIT.B0 = 1;
            PORTC.PODR.BIT.B0 = 1;
        }
        else {
            PORTC.PMR.BIT.B0 = 1;
            MTU3.TGRD = (uint16_t) (MTU3.TGRC * duty);
        }

        MTU.TSTRA.BIT.CST3 = 1;
    }

    void setDutyPA2MTU7A(float duty){
        duty = std::clamp<float>(duty, 0.0f, 1.0f);
        dutyPA2MTU7A = duty;

        if (std::fabs(duty) < FLT_EPSILON) {
            MTU.TSTRB.BIT.CST7 = 0;
            PORTA.PMR.BIT.B2 = 0;
            PORTA.PDR.BIT.B2 = 1;
            PORTA.PODR.BIT.B2 = 0;            
        }
        else if(duty >= 1.0f) {
            MTU.TSTRB.BIT.CST7 = 0;
            PORTA.PMR.BIT.B2 = 0;
            PORTA.PDR.BIT.B2 = 1;
            PORTA.PODR.BIT.B2 = 1;            
        }
        else {
            PORTA.PMR.BIT.B2 = 1;
            MTU7.TGRD = (uint16_t) (MTU7.TGRC * duty);
        }

        MTU.TSTRB.BIT.CST7 = 1;
    }

    void setDutyP23GPTA0(float duty){
        duty = std::clamp<float>(duty, 0.0f, 1.0f);
        dutyP23GPTA0 = duty;

        if (std::fabs(duty) < FLT_EPSILON) {
            GPT.GTSTR.BIT.CST0 = 0;
            PORT2.PMR.BIT.B3 = 0;
            PORT2.PDR.BIT.B3 = 1;
            PORT2.PODR.BIT.B3 = 0;
        }
        else if(duty >= 0.9999f) {
            GPT.GTSTR.BIT.CST0 = 0;
            PORT2.PMR.BIT.B3 = 0;
            PORT2.PDR.BIT.B3 = 1;
            PORT2.PODR.BIT.B3 = 1;
        }
        else {
            PORT2.PMR.BIT.B3 = 1;                 
            GPT0.GTCCRA = (uint16_t) (GPT0.GTPR * duty);
            GPT.GTSTR.BIT.CST0 = 1;
        }        
    }

    void setDutyP24MTU4A(float duty){
        duty = std::clamp<float>(duty, 0.0f, 1.0f);
        dutyP24MTU4A = duty;

        if (std::fabs(duty) < FLT_EPSILON) {
            MTU.TSTRA.BIT.CST4 = 0;
            PORT2.PMR.BIT.B4 = 0;
            PORT2.PDR.BIT.B4 = 1;
            PORT2.PODR.BIT.B4 = 0;
        }
        else if(duty >= 1.0f) {
            MTU.TSTRA.BIT.CST4 = 0;
            PORT2.PMR.BIT.B4 = 0;
            PORT2.PDR.BIT.B4 = 1;
            PORT2.PODR.BIT.B4 = 1;
        }
        else {
            PORT2.PMR.BIT.B4 = 1;
            MTU4.TGRD = (uint16_t) (MTU4.TGRC * duty);
            MTU.TSTRA.BIT.CST4 = 1;
        }        
    }

    float getDutyPA1MTU0B(){return dutyPA1MTU0B;};
    float getDutyPC3GPTA1(){return dutyPC3GPTA1;};
    float getDutyPC2GPTA2(){return dutyPC2GPTA2;};
    float getDutyPC1MTU3A(){return dutyPC1MTU3A;};
    float getDutyPC0MTU3C(){return dutyPC0MTU3C;};
    float getDutyPA0MTU7A(){return dutyPA2MTU7A;};
    float getDutyP23GPTA0(){return dutyP23GPTA0;};
    float getDutyP24MTU4A(){return dutyP24MTU4A;};
}
