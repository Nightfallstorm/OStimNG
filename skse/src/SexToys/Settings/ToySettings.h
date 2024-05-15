#pragma once

#include "SlotSettings.h"

namespace Toys {
    namespace Settings {
        struct ToySettings {
        public:
            bool enabled = true;
            SynchronizationType synchronizationType = SynchronizationType::PLAYER;
            bool climax = true;
            float climaxMagnitude = 1.0f;
            std::unordered_map<std::string, SlotSettings> slotSettings;

            SlotSettings* getSlotSettings(std::string slot);
            SlotSettings* getSlotSettingsUnsafe(std::string slot);

            void serialize(GameAPI::GameSerializationInterface serial);
            void deserialize(GameAPI::GameSerializationInterface serial);

            json toJson();
            void loadJson(json& json);
        };
    }
}