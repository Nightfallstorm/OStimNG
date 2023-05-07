#pragma once

#include <shared_mutex>

#include "ThreadActor.h"

#include "Alignment/ActorAlignment.h"
#include "Alignment/ThreadKey.h"
#include "Graph/Node.h"
#include "Serial/OldThread.h"

namespace OStim {

    using ThreadId = int64_t;
    class Thread : public RE::BSTEventSink<RE::BSAnimationGraphEvent>{
    public:
        ThreadId m_threadId;
        Graph::Node* m_currentNode = nullptr;
        bool isPlayerThread = false;
        std::map<int32_t, ThreadActor> m_actors;

        Thread(ThreadId id, RE::TESObjectREFR* furniture, std::vector<RE::Actor*> actors);

        ~Thread();

        void initContinue();

        std::string getAlignmentKey();
        Alignment::ActorAlignment getActorAlignment(int index);
        void updateActorAlignment(int index, Alignment::ActorAlignment alignment);
        void alignActors();
        
        void ChangeNode(Graph::Node* a_node);
        Graph::Node* getCurrentNode();

        void navigateTo(Graph::Node* node);

        void AddActor(RE::Actor* a_actor);
        void RemoveActor();

        void loop();

        ThreadActor* GetActor(RE::Actor* a_actor);
        ThreadActor* GetActor(int a_position);
        int getActorPosition(RE::Actor* actor);

        void SetSpeed(int speed);

        void callEvent(std::string eventName, int actorIndex, int targetIndex, int performerIndex);

        void close();

        RE::TESObjectREFR* GetStageObject() { return vehicle; }


    public:
        virtual RE::BSEventNotifyControl ProcessEvent(const RE::BSAnimationGraphEvent* a_event, RE::BSTEventSource<RE::BSAnimationGraphEvent>* a_eventSource) override;

        Serialization::OldThread serialize();

    private:
        RE::TESObjectREFR* furniture;
        RE::TESForm* furnitureOwner = nullptr;
        RE::TESObjectREFR* vehicle;
        std::shared_mutex nodeLock;

        int m_currentNodeSpeed = 0;
        std::string alignmentKey;

        float freeCamSpeedBefore = 0;
        float worldFOVbefore = 0;

        void addActorInner(int index, RE::Actor* actor);
        void addActorSink(RE::Actor* a_actor);
        void removeActorSink(RE::Actor* a_actor);

        void rebuildAlignmentKey();
        void alignActor(ThreadActor* threadActor, Alignment::ActorAlignment alignment);
    };

}  // namespace OStim