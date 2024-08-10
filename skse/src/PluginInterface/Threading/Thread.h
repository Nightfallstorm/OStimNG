#pragma once

#include "ThreadActor.h"
#include "ThreadActorVisitor.h"

#include "../Graph/Node.h"

namespace OStim {
    class Thread {
    public:
        virtual int32_t getThreadID() = 0;

        virtual bool isPlayerThread() = 0;

        virtual uint32_t getActorCount() = 0;
        virtual ThreadActor* getActor(uint32_t position) = 0;
        virtual void forEachThreadActor(ThreadActorVisitor* visitor) = 0;

        virtual Node* getCurrentNode() = 0;
    };
}