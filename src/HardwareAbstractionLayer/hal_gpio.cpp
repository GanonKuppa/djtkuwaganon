#include "hal_gpio.h"

#ifndef SILS
#include <PeripheralDriverLayer/pd_gpio.h>
#endif

namespace hal {

    void initGpio() {
#ifndef SILS
        peripheral_driver::initUnusePin();
        #ifdef DJTKUWAGANON_ACT1
        peripheral_driver::initDoutP22();
        peripheral_driver::initDoutP21();
        peripheral_driver::initDoutP20();
        peripheral_driver::initDoutP44();
        peripheral_driver::initDoutP43();
        peripheral_driver::initDoutP46();
        peripheral_driver::initDoutP17();
        peripheral_driver::initDoutPC5();
        #endif

        #ifdef DJTKUWAGANON_ACT2
        peripheral_driver::initDoutP14();
        peripheral_driver::initDoutP22();
        peripheral_driver::initDoutP20();
        peripheral_driver::initDoutP51();
        peripheral_driver::initDoutPC5();
        peripheral_driver::initDoutP13();
        peripheral_driver::initDoutP17();
        peripheral_driver::initDoutP21();
        #endif

        setDout0(false);
        setDout1(false);
        setDout2(false);
        setDout3(false);
        setDout4(false);
        setDout5(false);
        setDout6(false);
        setDout7(false);
#endif
    }

    void setDout0(bool out) {
#ifndef SILS
        #ifdef DJTKUWAGANON_ACT1        
        peripheral_driver::setDoutP22(out);
        #endif

        #ifdef DJTKUWAGANON_ACT2
        peripheral_driver::setDoutP14(out);
        #endif
#endif
    }

    void setDout1(bool out) {
#ifndef SILS
        #ifdef DJTKUWAGANON_ACT1        
        peripheral_driver::setDoutP21(out);
        #endif

        #ifdef DJTKUWAGANON_ACT2
        peripheral_driver::setDoutP22(out);
        #endif
#endif
    }

    void setDout2(bool out) {
#ifndef SILS
        #ifdef DJTKUWAGANON_ACT1        
        peripheral_driver::setDoutP20(out);
        #endif

        #ifdef DJTKUWAGANON_ACT2
        peripheral_driver::setDoutP20(out);
        #endif
#endif
    }

    void setDout3(bool out) {
#ifndef SILS
        #ifdef DJTKUWAGANON_ACT1        
        peripheral_driver::setDoutP44(out);
        #endif

        #ifdef DJTKUWAGANON_ACT2
        peripheral_driver::setDoutP51(out);
        #endif
#endif
    }

    void setDout4(bool out) {
#ifndef SILS
        #ifdef DJTKUWAGANON_ACT1        
        peripheral_driver::setDoutP43(out);
        #endif

        #ifdef DJTKUWAGANON_ACT2
        peripheral_driver::setDoutPC5(out);
        #endif
#endif
    }

    void setDout5(bool out) {
#ifndef SILS
        #ifdef DJTKUWAGANON_ACT1        
        peripheral_driver::setDoutP46(out);
        #endif

        #ifdef DJTKUWAGANON_ACT2
        peripheral_driver::setDoutP13(out);
        #endif
#endif
    }

    void setDout6(bool out) {
#ifndef SILS
        #ifdef DJTKUWAGANON_ACT1        
        peripheral_driver::setDoutP17(out);
        #endif

        #ifdef DJTKUWAGANON_ACT2
        peripheral_driver::setDoutP17(out);
        #endif
#endif
    }

    void setDout7(bool out) {
#ifndef SILS
        #ifdef DJTKUWAGANON_ACT1        
        peripheral_driver::setDoutPC5(out);
        #endif

        #ifdef DJTKUWAGANON_ACT2
        peripheral_driver::setDoutP21(out);
        #endif
#endif
    }

}

