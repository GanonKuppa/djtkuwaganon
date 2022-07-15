#include "hal_pwm.h"

#ifndef SILS
#include <PeripheralDriverLayer/pd_pwm.h>
#endif

namespace hal {
    void initPWM0() {
#ifndef SILS

    #ifdef DJTKUWAGANON_ACT1
    peripheral_driver::initPA1MTU0B();
    #endif

    #ifdef DJTKUWAGANON_ACT2
    peripheral_driver::initP23GPTA0();
    #endif

#endif
    }

    void initPWM1() {
#ifndef SILS

    #ifdef DJTKUWAGANON_ACT1
    peripheral_driver::initPC3GPTA1();
    #endif

    #ifdef DJTKUWAGANON_ACT2
    peripheral_driver::initPC1MTU3A();
    #endif

#endif
    }

    void initPWM2() {
#ifndef SILS

    #ifdef DJTKUWAGANON_ACT1
    peripheral_driver::initPC2GPTA2();
    #endif

    #ifdef DJTKUWAGANON_ACT2
    peripheral_driver::initPC2GPTA2();
    #endif

#endif
    }

    void initPWM3() {
#ifndef SILS

    #ifdef DJTKUWAGANON_ACT1
    peripheral_driver::initPC1MTU3A();
    #endif

    #ifdef DJTKUWAGANON_ACT2
    peripheral_driver::initPC3GPTA1();
    #endif

#endif
    }

    void initPWM4() {
#ifndef SILS

    #ifdef DJTKUWAGANON_ACT1
    peripheral_driver::initPC0MTU3C();
    #endif

    #ifdef DJTKUWAGANON_ACT2
    peripheral_driver::initPC0MTU3C();
    #endif

#endif
    }

    void initPWM5() {
#ifndef SILS
        
    #ifdef DJTKUWAGANON_ACT1
    peripheral_driver::initPA2MTU7A();
    #endif

    #ifdef DJTKUWAGANON_ACT2
    peripheral_driver::initP24MTU4A();
    #endif
                
#endif
    }



    void setDutyPWM0(float duty) {
#ifndef SILS

    #ifdef DJTKUWAGANON_ACT1
    peripheral_driver::setDutyPA1MTU0B(duty);
    #endif

    #ifdef DJTKUWAGANON_ACT2
    peripheral_driver::setDutyP23GPTA0(duty);
    #endif


#endif
    }

    void setDutyPWM1(float duty) {
#ifndef SILS

    #ifdef DJTKUWAGANON_ACT1
    peripheral_driver::setDutyPC3GPTA1(duty);
    #endif

    #ifdef DJTKUWAGANON_ACT2
    peripheral_driver::setDutyPC1MTU3A(duty);
    #endif

#endif
    }

    void setDutyPWM2(float duty) {
#ifndef SILS

    #ifdef DJTKUWAGANON_ACT1
    peripheral_driver::initPC2GPTA2(duty);
    #endif

    #ifdef DJTKUWAGANON_ACT2
    peripheral_driver::setDutyPC2GPTA2(duty);
    #endif

#endif
    }

    void setDutyPWM3(float duty) {
#ifndef SILS

    #ifdef DJTKUWAGANON_ACT1
    peripheral_driver::setDutyPC1MTU3A(duty);
    #endif

    #ifdef DJTKUWAGANON_ACT2
    peripheral_driver::setDutyPC3GPTA1(duty);
    #endif

#endif
    }

    void setDutyPWM4(float duty) {
#ifndef SILS

    #ifdef DJTKUWAGANON_ACT1
    peripheral_driver::setDutyPC0MTU3C(duty);
    #endif

    #ifdef DJTKUWAGANON_ACT2
    peripheral_driver::setDutyPC0MTU3C(duty);
    #endif

#endif
    }

    void setDutyPWM5(float duty) {
#ifndef SILS

    #ifdef DJTKUWAGANON_ACT1
    peripheral_driver::setDutyPA2MTU7A(duty);
    #endif

    #ifdef DJTKUWAGANON_ACT2
    peripheral_driver::setDutyP24MTU4A(duty);
    #endif

#endif
    }



    float getDutyPWM0() {
#ifndef SILS
        
    #ifdef DJTKUWAGANON_ACT1
    return peripheral_driver::getDutyPA1MTU0B();
    #endif

    #ifdef DJTKUWAGANON_ACT2
    return peripheral_driver::getDutyP23GPTA0();
    #endif
    return 0.0f;
#else
        return 0.0f;
#endif

    }

    float getDutyPWM1() {
#ifndef SILS

    #ifdef DJTKUWAGANON_ACT1
    return peripheral_driver::getDutyPC2GPTA2();
    #endif

    #ifdef DJTKUWAGANON_ACT2
    return peripheral_driver::getDutyPC1MTU3A();
    #endif
    return 0.0f;
#else
        return 0.0f;
#endif

    }

    float getDutyPWM2() {
#ifndef SILS

    #ifdef DJTKUWAGANON_ACT1
    return peripheral_driver::getDutyPC2GPTA1();
    #endif

    #ifdef DJTKUWAGANON_ACT2
    return peripheral_driver::getDutyPC3GPTA1();
    #endif
    return 0.0f;
#else
        return 0.0f;
#endif

    }

    float getDutyPWM3() {
#ifndef SILS

    #ifdef DJTKUWAGANON_ACT1
    return peripheral_driver::getDutyPC1MTU3A();
    #endif

    #ifdef DJTKUWAGANON_ACT2
    return peripheral_driver::getDutyPC3GPTA1();
    #endif
    return 0.0f;
#else
        return 0.0f;
#endif

    }

    float getDutyPWM4() {
#ifndef SILS

    #ifdef DJTKUWAGANON_ACT1
    return peripheral_driver::getDutyPC0MTU3C();
    #endif

    #ifdef DJTKUWAGANON_ACT2
    return peripheral_driver::getDutyPC0MTU3C();
    #endif
    return 0.0f;
#else
        return 0.0f;
#endif
    }

    float getDutyPWM5() {
#ifndef SILS

    #ifdef DJTKUWAGANON_ACT1
    return peripheral_driver::getDutyPA2MTU7A();
    #endif

    #ifdef DJTKUWAGANON_ACT2
    return peripheral_driver::getDutyP24MTU4A();
    #endif
    return 0.0f;
#else
        return 0.0f;
#endif
    }



}
