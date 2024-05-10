#pragma once

#include "ThreadStarter/ThreadStartParams.h"
#include "Singleton.h"
#include "Thread.h"

#include "GameAPI/GameActor.h"
#include "Serial/OldThread.h"
#include "Util/IDGenerator.h"
#include <shared_mutex>

namespace OStim {    
    class ThreadManager final : public ISingleton<ThreadManager> {
    public:
        ThreadManager();
        int startThread(ThreadStartParams params);
        Thread* GetThread(ThreadId a_id);
        Thread* getPlayerThread();
        void queueThreadStop(ThreadId threadID);
        void UntrackAllThreads();
        bool AnySceneRunning();
        bool playerThreadRunning();
        inline int getThreadCount() { return m_threadMap.size(); }


        Thread* findThread(GameAPI::GameActor actor);

        ThreadActor* findActor(GameAPI::GameActor actor);

        std::vector<Serialization::OldThread> serialize();

    private:
        using ThreadMap = std::unordered_map<ThreadId, Thread*>;
        Util::IDGenerator idGenerator = Util::IDGenerator(1);
        std::shared_mutex m_threadMapMtx;
        ThreadMap m_threadMap;
        std::thread m_excitementThread;
        std::vector<ThreadId> threadStopQueue;

        void stopThreadNoLock(ThreadId threadID);

#pragma region events
    public:
        inline void registerThreadStartListener(std::function<void(Thread*)> listener) { threadStartListeners.push_back(listener); }

    private:
        std::vector<std::function<void(Thread*)>> threadStartListeners;
#pragma endregion
    };
}  // namespace OStim