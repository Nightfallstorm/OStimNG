#pragma once

#include "GameAPI/GameActor.h"
#include "GameLogic/GameTable.h"

namespace GameAPI {
    class Game {
    public:
        inline static bool isPaused() { return RE::UI::GetSingleton()->GameIsPaused(); }
        inline static float getTimeScale() { return GameLogic::GameTable::getTimescale()->value; }
        inline static void setTimeScale(float scale) { GameLogic::GameTable::getTimescale()->value = scale; }
        static void setGameSpeed(float speed);
        static void shakeController(float leftStrength, float rightStrength, float duration);
        static GameActor getCrosshairActor();

        inline static void notification(std::string text) { RE::DebugNotification(text.c_str()); }
        inline static int getMessageBoxOptionLimit() { return 9; }
        static void showMessageBox(std::string content, std::vector<std::string> options, std::function<void(unsigned int)> callback);

        static inline void runSynced(std::function<void()> func) { SKSE::GetTaskInterface()->AddTask([func]{func();}); }

    private:
        class MessageBoxCallback : public RE::IMessageBoxCallback {
        public:
            MessageBoxCallback(std::function<void(unsigned int)> callback) : callback{callback} {}
            ~MessageBoxCallback() override {}
            void Run(RE::IMessageBoxCallback::Message message) override { callback(static_cast<unsigned int>(message)); }
        private:
            std::function<void(unsigned int)> callback;
        };

        inline static void ShakeController(bool leftMotor, float strength, float duration) {
            using func_t = decltype(ShakeController);
            REL::Relocation<func_t> func{RELOCATION_ID(67220, 68528)};
            func(leftMotor, strength, duration);
        }
    };
}