#pragma once

#include <stdint.h>

#include "baseModule.h"
#include "turnEnum.h"


namespace module {

    class TrajInfo {
      public:
        ETurnType turn_type_next = ETurnType::NONE;
        ETurnDir turn_dir_next = ETurnDir::NO_TURN;
        ECornerType corner_type = ECornerType::NONE;
        int16_t wall_sensor_max = 0;
        int16_t wall_sensor_min = 32767;
        int16_t wall_sensor_buff_max = 0;
        float end_yaw;
        float end_x;
        float detected_x;
        float end_y;
        float detected_y;
    };

    class RunAnalizer : public BaseModule<RunAnalizer> {
      public:
        void update0();
        void debug();
        void print();
      private:
        static constexpr uint16_t TRAJ_INFO_MAX = 100;
        TrajInfo _traj_info_list[TRAJ_INFO_MAX];
        uint16_t _traj_info_num;
        bool _in_detect_edge_area_pre;
        bool _detected_edge_pre;
        friend class BaseModule<RunAnalizer>;
        RunAnalizer();
    };

    int usrcmd_runAnalizer(int argc, char** argv);

}
