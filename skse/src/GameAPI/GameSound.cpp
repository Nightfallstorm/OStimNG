#include "GameSound.h"

namespace GameAPI {
    void GameSound::play(GameActor actor, float volume) {
        //FOR VR VERSION
        auto* audioManager = RE::BSAudioManager::GetSingleton();
        if (!audioManager || !form) {
            return;
        }

        RE::BSSoundHandle newHandle;

        if (!audioManager->GetSoundHandle(newHandle, form, 0x10) || !newHandle.IsValid()) {
            return;
        }

        if (actor.form) {
            if (auto* actor3D = actor.form->Get3D()) {
                newHandle.SetObjectToFollow(actor3D);
            }
        }

        newHandle.SetVolume(volume);

        if (newHandle.Play()) {
            handle = newHandle;
        }
        //
    }
}