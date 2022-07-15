#include <PeripheralDriverLayer/pd_gpio.h>
#include <stdint.h>
#include "iodefine.h"

namespace peripheral_driver {
    void initUnusePin() {
        // 未使用ピンの処理
        PORT0.PDR.BYTE = (uint8_t) (PORT0.PDR.BYTE | 0x0F);
        PORT1.PDR.BYTE = (uint8_t) (PORT1.PDR.BYTE | 0x03);
        PORT5.PDR.BYTE = (uint8_t) (PORT5.PDR.BYTE | 0x40);
        PORT6.PDR.BYTE = (uint8_t) (PORT6.PDR.BYTE | 0xFF);
        PORT7.PDR.BYTE = (uint8_t) (PORT7.PDR.BYTE | 0xFF);
        PORT8.PDR.BYTE = (uint8_t) (PORT8.PDR.BYTE | 0xCF);
        PORT9.PDR.BYTE = (uint8_t) (PORT9.PDR.BYTE | 0xFF);
        PORTF.PDR.BYTE = (uint8_t) (PORTF.PDR.BYTE | 0x3F);
        PORTG.PDR.BYTE = (uint8_t) (PORTG.PDR.BYTE | 0xFF);
        PORTJ.PDR.BYTE = (uint8_t) (PORTJ.PDR.BYTE | 0x20);
    }

    void initDoutP22(){PORT2.PDR.BIT.B2 = 1;}
    void initDoutP21(){PORT2.PDR.BIT.B1 = 1;}
    void initDoutP20(){PORT2.PDR.BIT.B0 = 1;}
    void initDoutP44(){PORT4.PDR.BIT.B4 = 1;}
    void initDoutP43(){PORT4.PDR.BIT.B3 = 1;}
    void initDoutP46(){PORT4.PDR.BIT.B6 = 1;}
    void initDoutP17(){PORT1.PDR.BIT.B7 = 1;}
    void initDoutPC5(){PORTC.PDR.BIT.B5 = 1;}
    void initDoutP14(){PORT1.PDR.BIT.B4 = 1;}
    void initDoutP51(){PORT5.PDR.BIT.B1 = 1;}
    void initDoutP13(){PORT1.PDR.BIT.B3 = 1;}

    void setDoutP22(bool out){PORT2.PODR.BIT.B2 = out;}
    void setDoutP21(bool out){PORT2.PODR.BIT.B1 = out;}
    void setDoutP20(bool out){PORT2.PODR.BIT.B0 = out;}
    void setDoutP44(bool out){PORT4.PODR.BIT.B4 = out;}
    void setDoutP43(bool out){PORT4.PODR.BIT.B3 = out;}
    void setDoutP46(bool out){PORT4.PODR.BIT.B6 = out;}    
    void setDoutP17(bool out){PORT1.PODR.BIT.B7 = out;}
    void setDoutPC5(bool out){PORTC.PODR.BIT.B5 = out;}
    void setDoutP14(bool out){PORT1.PODR.BIT.B4 = out;}
    void setDoutP51(bool out){PORT5.PODR.BIT.B1 = out;}
    void setDoutP13(bool out){PORT1.PODR.BIT.B3 = out;}
}
