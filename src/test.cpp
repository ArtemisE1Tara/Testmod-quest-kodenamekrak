#include "hooks.hpp"
#include "GlobalNamespace/MultiplayerGameplayAnimator.hpp"
#include "GlobalNamespace/GameplaySetupViewController.hpp"
#include "GlobalNamespace/GameplaySetupViewController_Panel.hpp"
#include "questui/shared/BeatSaberUI.hpp"
#include "questui/shared/QuestUI.hpp"
#include "config-utils/shared/config-utils.hpp"
#include "ModConfig.hpp"
#include "VRUIControls/VRGraphicRaycaster.hpp"
#include "logos.hpp"


using namespace GlobalNamespace;
using namespace QuestUI;
using namespace UnityEngine;
using namespace UnityEngine::UI;
using namespace HMUI;
using namespace TMPro;
bool showScreen = true;

MAKE_AUTO_HOOK_MATCH(ToggleTest, &GameplaySetupViewController::DidActivate, void, GameplaySetupViewController* self, bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling){

ToggleTest(self, firstActivation, addedToHierarchy, screenSystemEnabling);
if(firstActivation){
    // tried to create empty text to attatch stuff to
    //auto text = QuestUI::BeatSaberUI::CreateText(self->get_transform(), "", UnityEngine::Vector2(50.0f, -80.0f), UnityEngine::Vector2(100.0f, 100.0f));
    
    // remembered floating screens exist
    UnityEngine::GameObject* testScreen = QuestUI::BeatSaberUI::CreateFloatingScreen(UnityEngine::Vector2(15.0f, 10.0f), UnityEngine::Vector3(0.0f, 2.0f, 2.0f), UnityEngine::Vector3(180, 0, 0), 0.0f, true, true, 3);


    QuestUI::BeatSaberUI::CreateText(testScreen->get_transform(), getModConfig().Test.GetValue(), UnityEngine::Vector2(11.0f, 11.0f));

    // similar place and same size as randomsongpicker because i use it so it just looks nicer if they are both the same size
    auto button = QuestUI::BeatSaberUI::CreateUIButton(self->get_transform(), "", UnityEngine::Vector2(56.0f, -15.0f), [&](){
        auto Screen1 = testScreen->get_gameObject();
        if(showScreen){
            showScreen = false;
            Screen1->SetActive(false);
        }
        else{
            Screen1->SetActive(true);
            showScreen = true;
        }

    });
        auto *image = QuestUI::BeatSaberUI::CreateImage(button->get_transform(), QuestUI::BeatSaberUI::Base64ToSprite(CrossLogo));
        image->get_rectTransform()->set_localScale({0.7f, 0.7f, 1.0f});

}
}