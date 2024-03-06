#include "Game.h"

#include "GameUtil.h"

#include "Game/LocaleManager.h"

namespace GameAPI {
    void Game::setGameSpeed(float speed) {
        const auto scriptFactory = RE::IFormFactory::GetConcreteFormFactoryByType<RE::Script>();
        const auto script = scriptFactory ? scriptFactory->Create() : nullptr;
        if (script) {
            script->SetCommand("sgtm " + std::to_string(speed));
            GameUtil::CompileAndRun(script, RE::PlayerCharacter::GetSingleton());
            delete script;
        }
    }

    void Game::shakeController(float leftStrength, float rightStrength, float duration) {
        ShakeController(true, leftStrength, duration);
        ShakeController(true, rightStrength, duration);
    }

    GameActor Game::getCrosshairActor() {
        if (GameLogic::GameTable::getCurrentCrosshairRef()) {
            return GameLogic::GameTable::getCurrentCrosshairRef()->As<RE::Actor>();
        } else {
            return {};
        }
    }

    void Game::showMessageBox(std::string content, std::vector<std::string> options, std::function<void(unsigned int)> callback) {
        content = LocaleManager::GetSingleton()->GetLocalization(content);
        for (std::string& option : options) {
            option = LocaleManager::GetSingleton()->GetLocalization(option);
        }

        auto* messagebox = RE::MessageDataFactoryManager::GetSingleton()->GetCreator<RE::MessageBoxData>(RE::InterfaceStrings::GetSingleton()->messageBoxData)->Create();
        messagebox->callback = RE::make_smart<MessageBoxCallback>(callback);
        messagebox->bodyText = content;
        for (std::string& text : options) {
            messagebox->buttonText.push_back(text.c_str());
        }
        messagebox->QueueMessage();
    }
}