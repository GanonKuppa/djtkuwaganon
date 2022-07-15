#include <stdint.h>
#include "hal_ad.h"

#ifndef SILS
#include <PeripheralDriverLayer/pd_ad.h>
#endif

namespace hal {
    void initAD() {
#ifndef SILS
        #ifdef DJTKUWAGANON_ACT1        
        peripheral_driver::initAD_AN113();
        peripheral_driver::initAD_AN108();
        peripheral_driver::initAD_AN110();
        peripheral_driver::initAD_AN111();
        peripheral_driver::initAD_AN101();
        peripheral_driver::initS12AD1();
        #endif

        #ifdef DJTKUWAGANON_ACT2
        peripheral_driver::initAD_AN101();
        peripheral_driver::initAD_AN100();
        peripheral_driver::initAD_AN112();
        peripheral_driver::initAD_AN108();
        peripheral_driver::initAD_AN003();
        peripheral_driver::initS12AD0();
        peripheral_driver::initS12AD1();        
        #endif
#endif
    }

    uint16_t startAD0() {
#ifndef SILS
        #ifdef DJTKUWAGANON_ACT1        
        return peripheral_driver::startAD_AN113();
        #endif

        #ifdef DJTKUWAGANON_ACT2
        return peripheral_driver::startAD_AN101();
        #endif        
#else
        return 0;
#endif

    }

    uint16_t startAD1() {
#ifndef SILS
        #ifdef DJTKUWAGANON_ACT1        
        return peripheral_driver::startAD_AN101();
        #endif

        #ifdef DJTKUWAGANON_ACT2
        return peripheral_driver::startAD_AN003();
        #endif
#else
        return 0;

#endif

    }

    uint16_t startAD2() {
#ifndef SILS
        #ifdef DJTKUWAGANON_ACT1        
        return peripheral_driver::startAD_AN111();
        #endif

        #ifdef DJTKUWAGANON_ACT2
        return peripheral_driver::startAD_AN108();
        #endif        
#else
        return 0;

#endif

    }

    uint16_t startAD3() {
#ifndef SILS
        #ifdef DJTKUWAGANON_ACT1        
        return peripheral_driver::startAD_AN110();
        #endif

        #ifdef DJTKUWAGANON_ACT2
        return peripheral_driver::startAD_AN112();
        #endif
#else
        return 0;
#endif

    }

    uint16_t startAD4() {
#ifndef SILS
        #ifdef DJTKUWAGANON_ACT1        
        return peripheral_driver::startAD_AN108();
        #endif

        #ifdef DJTKUWAGANON_ACT2
        return peripheral_driver::startAD_AN100();
        #endif        
#else
        return 0;
#endif

    }

    //uint16_t startAD5();
    //uint16_t startAD6();
    //uint16_t startAD7();

    uint16_t getAD0() {
#ifndef SILS
        #ifdef DJTKUWAGANON_ACT1        
        return peripheral_driver::getAD_AN113();
        #endif

        #ifdef DJTKUWAGANON_ACT2
        return peripheral_driver::getAD_AN101();
        #endif        
#else
        return 0;
#endif

    }

    uint16_t getAD1() {
#ifndef SILS
        #ifdef DJTKUWAGANON_ACT1        
        return peripheral_driver::getAD_AN101();
        #endif

        #ifdef DJTKUWAGANON_ACT2
        return peripheral_driver::getAD_AN003();
        #endif
#else
        return 0;

#endif

    }

    uint16_t getAD2() {
#ifndef SILS
        #ifdef DJTKUWAGANON_ACT1        
        return peripheral_driver::getAD_AN111();
        #endif

        #ifdef DJTKUWAGANON_ACT2
        return peripheral_driver::getAD_AN108();
        #endif        
#else
        return 0;

#endif

    }

    uint16_t getAD3() {
#ifndef SILS
        #ifdef DJTKUWAGANON_ACT1        
        return peripheral_driver::getAD_AN110();
        #endif

        #ifdef DJTKUWAGANON_ACT2
        return peripheral_driver::getAD_AN112();
        #endif
#else
        return 0;
#endif

    }

    uint16_t getAD4() {
#ifndef SILS
        #ifdef DJTKUWAGANON_ACT1        
        return peripheral_driver::getAD_AN108();
        #endif

        #ifdef DJTKUWAGANON_ACT2
        return peripheral_driver::getAD_AN100();
        #endif        
#else
        return 0;
#endif

    }


    //uint16_t getAD5();
    //uint16_t getAD6();
    //uint16_t getAD7();



}