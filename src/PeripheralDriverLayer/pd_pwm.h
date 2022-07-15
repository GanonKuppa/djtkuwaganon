#pragma once

namespace peripheral_driver {

    void initPA1MTU0B();
    void initPC3GPTA1();
    void initPC2GPTA2();
    void initPC1MTU3A();
    void initPC0MTU3C();
    void initPA2MTU7A();
    void initP23GPTA0();
    void initP24MTU4A();

    void setDutyPA1MTU0B(float duty);
    void setDutyPC3GPTA1(float duty);
    void setDutyPC2GPTA2(float duty);
    void setDutyPC1MTU3A(float duty);
    void setDutyPC0MTU3C(float duty);
    void setDutyPA2MTU7A(float duty);
    void setDutyP23GPTA0(float duty);
    void setDutyP24MTU4A(float duty);

    float getDutyPA1MTU0B();
    float getDutyPC3GPTA1();
    float getDutyPC2GPTA2();
    float getDutyPC1MTU3A();
    float getDutyPC0MTU3C();
    float getDutyPA2MTU7A();
    float getDutyP23GPTA0();
    float getDutyP24MTU4A();


}