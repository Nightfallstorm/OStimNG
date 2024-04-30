#pragma once

#include "../../PeakType.h"
#include "BoneDistancePeakTypeParams.h"

namespace Graph {
    namespace Action {
        namespace Peak {
            class BoneDistancePeakType : public PeakType {
            public:
                BoneDistancePeakType(PeakTypeParams params, BoneDistancePeakTypeParams boneParams);

                virtual Threading::Thread::Peak::PeakHandler* create(Threading::Thread::Peak::PeakHandlerParams params, GameAPI::GameActor actor, GameAPI::GameActor target);

            private:
                bool inverse;
                std::vector<std::string> actorBones;
                std::vector<std::string> targetBones;
            };
        }
    }
}