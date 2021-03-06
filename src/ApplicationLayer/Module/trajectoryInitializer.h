#pragma once

#include <memory>
#include <unordered_map>


#include "baseModule.h"
#include "turnParameter.h"
#include "turnEnum.h"
#include "turnPreCalculations.h"


namespace module {
    class TrajectoryInitializer : public BaseModule<TrajectoryInitializer> {
      public:
        float getV(ETurnParamSet tp, ETurnType tt);
        float getAcc(ETurnParamSet tp, ETurnType tt);
        float getPreDist(ETurnParamSet tp, ETurnType tt);
        float getFolDist(ETurnParamSet tp, ETurnType tt);
        float getMoveX(ETurnParamSet tp, ETurnType tt);
        float getMoveY(ETurnParamSet tp, ETurnType tt);
        float getTrajEndTime(ETurnParamSet tp, ETurnType tt);
        TurnParameter getTurnParameter(ETurnParamSet tp);
        std::unique_ptr<TurnIterator> generateTurnIterator(ETurnParamSet tp, ETurnType tt);
        void debugMollifier();
        void debugParamSet();
        void debugPreCalcs();
      private:
        friend class BaseModule<TrajectoryInitializer>;
        TrajectoryInitializer();
        void _init();
        std::unordered_map<ETurnParamSet, TurnParameter> _turnParamSet;
        std::unordered_map<ETurnParamSet, TurnPreCalculations> _turnPreCalcs;
    };

    int usrcmd_trajectoryInitializer(int argc, char** argv);
}
