#pragma once

#ifndef SILS
#include <PeripheralDriverLayer/pd_timerInterrupt.h>
#endif

namespace hal {
    inline void enterCriticalSection() {
#ifndef SILS
        peripheral_driver::stopCMT0();
        peripheral_driver::stopCMT1();
#endif
    };

    inline void leaveCriticalSection() {
#ifndef SILS
        peripheral_driver::startCMT0();
#endif
    };
}
