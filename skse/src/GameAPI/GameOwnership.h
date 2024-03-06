#pragma once

#include "GameRecord.h"

namespace GameAPI {
    struct GameOwnership : public GameRecord<RE::TESForm> {
    public:
        GameOwnership() {}
        GameOwnership(RE::TESForm* form) { this->form = form; }
    };
}