#pragma once

namespace peripheral_driver {
    void initUnusePin();

    void initDoutP22();
    void initDoutP21();
    void initDoutP20();
    void initDoutP44();
    void initDoutP43();
    void initDoutP46();
    void initDoutP17();
    void initDoutPC5();
    void initDoutP14();
    void initDoutP51();
    void initDoutP13();

    void setDoutP22(bool out);
    void setDoutP21(bool out);
    void setDoutP20(bool out);
    void setDoutP44(bool out);
    void setDoutP43(bool out);
    void setDoutP46(bool out);
    void setDoutP17(bool out);
    void setDoutPC5(bool out);
    void setDoutP14(bool out);
    void setDoutP51(bool out);
    void setDoutP13(bool out);

}