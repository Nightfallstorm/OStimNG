#pragma once

#include "ActorPropertyList.h"
#include "EquipObject.h"
#include "FacialExpression.h"

#include "GameAPI/GameActor.h"
#include "GameAPI/GameCondition.h"

namespace Trait {
    class TraitTable {
    public:
        inline static FacialExpression fallbackExpression{};

        inline static std::unordered_map<int, FaceModifier> openMouthPhonemes;
        inline static std::unordered_map<int, FaceModifier> lickingPhonemes;

        static void setup();
        static void setupForms();

        static std::vector<FacialExpression*>* getExpressionsForActionActor(std::string);
        static std::vector<FacialExpression*>* getExpressionsForActionTarget(std::string);
        static std::vector<FacialExpression*>* getExpressionsForEvent(std::string);
        static std::vector<FacialExpression*>* getExpressionsForSet(std::string);

        static EquipObject* getRandomEquipObject(std::string type);
        static EquipObject* getEquipObject(GameAPI::GameActor actor, std::string type);

        static std::vector<std::string> getEquipObjectTypes();
        static std::vector<std::string> getEquipObjectPairs(RE::FormID formID, std::string type);
        static std::vector<std::string> getEquipObjectsOfType(std::string type);
        static std::string getEquipObjectName(RE::FormID formID, std::string type);
        static void setEquipObjectID(RE::FormID formID, std::string type, std::string id);

        inline static bool areFacialExpressionsBlocked(RE::Actor* actor) { return actor->IsInFaction(noFacialExpressionsFaction); }

    private:
        static void parseGender(std::string& path, nlohmann::json json, GenderExpression* genderExpression);
        static FaceModifier parseModifier(std::string& path, nlohmann::json json);
        static void addToTable(std::unordered_map<std::string, std::vector<FacialExpression*>*>* table, std::string key, FacialExpression* expression);
        static std::vector<FacialExpression*>* getExpressionsFromTable(std::unordered_map<std::string, std::vector<FacialExpression*>*> table, std::string key);

        inline static std::unordered_map<std::string, std::vector<FacialExpression*>*> expressionsByActionActors;
        inline static std::unordered_map<std::string, std::vector<FacialExpression*>*> expressionsByActionTargets;
        inline static std::unordered_map<std::string, std::vector<FacialExpression*>*> expressionsByEvents;
        inline static std::unordered_map<std::string, std::vector<FacialExpression*>*> expressionsBySets;

        inline static std::unordered_map<std::string, std::unordered_map<std::string, EquipObject*>> equipObjects;
        inline static std::unordered_map<std::string, EquipObject*> defaultEquipObjects;

        inline static RE::TESFaction* noFacialExpressionsFaction;

#pragma region actorProperties
    public:
        inline static std::string getActorType(GameAPI::GameActor actor) {return actorTypes.get(actor, "");}
        inline static std::string getActorExpression(GameAPI::GameActor actor) {return actorExpressions.get(actor, "");}
        inline static bool isActorMuted(GameAPI::GameActor actor) { return actorMutes.get(actor, false); }
        inline static bool isActorMuffled(GameAPI::GameActor actor) { return actorMuffles.get(actor, false); }
        static std::set<std::string> getActorRequirements(GameAPI::GameActor actor);

    private:
        inline static ActorPropertyList<std::string> actorTypes;
        inline static ActorPropertyList<std::string> actorExpressions;
        inline static ActorPropertyList<bool> actorMutes;
        inline static ActorPropertyList<bool> actorMuffles;
        inline static std::unordered_map<std::string, ActorPropertyList<bool>> actorRequirements;


        static void setupActorProperties();
#pragma endregion
    };
}