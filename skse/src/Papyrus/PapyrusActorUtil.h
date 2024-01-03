#pragma once

#include "GameAPI/GameCondition.h"
#include "Util/ActorUtil.h"
#include "Util/CompatibilityTable.h"
#include "Util/VectorUtil.h"

namespace PapyrusActorUtil {
    using VM = RE::BSScript::IVirtualMachine;

    bool HasSchlong(RE::StaticFunctionTag*, RE::Actor* actor) {
        return Compatibility::CompatibilityTable::hasSchlong(actor);
    }

    bool FulfillsCondition(RE::StaticFunctionTag*, RE::Actor* actor, RE::BGSPerk* condition) {
        return GameAPI::GameCondition{condition}.fulfills(actor);
    }

    bool FulfillsAnyCondition(RE::StaticFunctionTag*, RE::Actor* actor, std::vector<RE::BGSPerk*> conditions) {
        for (RE::BGSPerk* condition : conditions) {
            if (GameAPI::GameCondition{condition}.fulfills(actor)) {
                return true;
            }
        }
        return false;
    }

    bool FulfillsAllConditions(RE::StaticFunctionTag*, RE::Actor* actor, std::vector<RE::BGSPerk*> conditions) {
        for (RE::BGSPerk* condition : conditions) {
            if (!GameAPI::GameCondition{condition}.fulfills(actor)) {
                return false;
            }
        }
        return true;
    }

    void SayTo(RE::StaticFunctionTag*, RE::Actor* actor, RE::Actor* target, RE::TESTopic* dialogue) {
        GameAPI::GameDialogue(dialogue).sayTo(actor, target);
    }

    void SayAs(RE::StaticFunctionTag*, RE::Actor* actor, RE::Actor* target, RE::TESTopic* dialogue, RE::BGSVoiceType* voice) {
        GameAPI::GameDialogue(dialogue).sayAs(actor, target, voice);
    }

    std::vector<RE::Actor*> EmptyArray(RE::StaticFunctionTag*) {
        return {};
    }

    std::vector<RE::Actor*> ToArray(RE::StaticFunctionTag*, RE::Actor* one, RE::Actor* two, RE::Actor* three, RE::Actor* four, RE::Actor* five, RE::Actor* six, RE::Actor* seven, RE::Actor* eight, RE::Actor* nine, RE::Actor* ten) {
        std::vector<RE::Actor*> actors;

        if (one) actors.push_back(one);
        if (two) actors.push_back(two);
        if (three) actors.push_back(three);
        if (four) actors.push_back(four);
        if (five) actors.push_back(five);
        if (six) actors.push_back(six);
        if (seven) actors.push_back(seven);
        if (eight) actors.push_back(eight);
        if (nine) actors.push_back(nine);
        if (ten) actors.push_back(ten);

        return actors;
    }

    std::vector<RE::Actor*> Sort(RE::StaticFunctionTag*, std::vector<RE::Actor*> actors, std::vector<RE::Actor*> dominantActors, int playerIndex) {
        std::vector<GameAPI::GameActor> gameActors = GameAPI::GameActor::convertVector(actors);
        
        std::vector<GameAPI::GameActor> gameDoms = GameAPI::GameActor::convertVector(dominantActors);

        ActorUtil::sort(gameActors, gameDoms, playerIndex);

        std::vector<RE::Actor*> ret;
        for (GameAPI::GameActor actor : gameActors) {
            ret.push_back(actor.form);
        }

        return ret;
    }

    bool Bind(VM* a_vm) {
        const auto obj = "OActorUtil"sv;

        BIND(HasSchlong);
        BIND(FulfillsCondition);
        BIND(FulfillsAnyCondition);
        BIND(FulfillsAllConditions);

        BIND(SayTo);
        BIND(SayAs);

        BIND(EmptyArray);
        BIND(ToArray);

        BIND(Sort);

        return true;
    }
}