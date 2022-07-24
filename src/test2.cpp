#include "ModConfig.hpp"
#include "hooks.hpp"
#include "GlobalNamespace/FPSCounter.hpp"
#include "GlobalNamespace/FPSCounterUIController.hpp"
#include "GlobalNamespace/GameplayCoreInstaller.hpp"
#include "UnityEngine/Object.hpp"
#include "UnityEngine/Resources.hpp"
#include "questui/shared/BeatSaberUI.hpp"
#include "questui/shared/QuestUI.hpp"
#include "GlobalNamespace/CentralLeaderboardViewController.hpp"

using namespace GlobalNamespace;
using namespace UnityEngine;



MAKE_AUTO_HOOK_MATCH(BIGTEST, &GameplayCoreInstaller::InstallBindings, void, GameplayCoreInstaller* self){
    BIGTEST(self);  

    UnityEngine::GameObject* testScreen2 = QuestUI::BeatSaberUI::CreateFloatingScreen(UnityEngine::Vector2(1.0f, 1.0f), UnityEngine::Vector3(1.5f, 0.1f, 1.0f), UnityEngine::Vector3(0, 20, 180), 0.0f, true, true, 2);
    //auto text = QuestUI::BeatSaberUI::CreateText(testScreen2->get_transform(), "TEST", UnityEngine::Vector2(20.0f, 0.0f));

}
