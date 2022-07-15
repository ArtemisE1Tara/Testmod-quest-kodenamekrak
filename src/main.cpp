#include "main.hpp"
#include "GlobalNamespace/MainMenuViewController.hpp"
#include "GlobalNamespace/ResultsViewController.hpp"
#include "UnityEngine/UI/Button.hpp"
#include "UnityEngine/GameObject.hpp"
#include "HMUI/CurvedTextMeshPro.hpp"
#include "beatsaber-hook/shared/utils/hooking.hpp"
#include "questui/shared/QuestUI.hpp"
#include "questui/shared/BeatSaberUI.hpp"
#include "config-utils/shared/config-utils.hpp"
#include "ModConfig.hpp"
using namespace GlobalNamespace;
using namespace QuestUI;
DEFINE_CONFIG(ModConfig);

static ModInfo modInfo; // Stores the ID and version of our mod, and is sent to the modloader upon startup

// Loads the config from disk using our modInfo, then returns it for use
Configuration& getConfig() {
    static Configuration config(modInfo);
    config.Load();
    return config;
}

// Returns a logger, useful for printing debug messages
Logger& getLogger() {
    static Logger* logger = new Logger(modInfo);
    return *logger;
}

// Called at the early stages of game loading
extern "C" void setup(ModInfo& info) {
    info.id = ID;
    info.version = VERSION;
    modInfo = info;
	
    getConfig().Load(); // Load the config file
    getLogger().info("Completed setup!");
}

MAKE_HOOK_MATCH(MainMenuSoloHook, &GlobalNamespace::MainMenuViewController::DidActivate, void, GlobalNamespace::MainMenuViewController
*self, bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling) {
    MainMenuSoloHook(self, firstActivation, addedToHierarchy, screenSystemEnabling);
    
    UnityEngine::UI::Button *soloMenuButton = self->dyn__soloButton();
    UnityEngine::GameObject *gameObject = soloMenuButton->get_gameObject();
    HMUI::CurvedTextMeshPro *soloMenuText = gameObject->GetComponentInChildren<HMUI::CurvedTextMeshPro *>();

    if(getModConfig().SoloToggle.GetValue() == 0){
    soloMenuText->SetText("SOLO!");
    }
    else if(getModConfig().SoloToggle.GetValue() == 1){
    soloMenuText->SetText(getModConfig().SoloButton.GetValue());
    }
    else{
        getModConfig().SoloToggle.SetValue(0);
    }
  }
  
  MAKE_HOOK_MATCH(MainMenuPartyHook, &GlobalNamespace::MainMenuViewController::DidActivate, void, GlobalNamespace::MainMenuViewController
*self, bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling) {
    MainMenuPartyHook(self, firstActivation, addedToHierarchy, screenSystemEnabling);

    UnityEngine::UI::Button *partyMenuButton = self->dyn__partyButton();
    UnityEngine::GameObject *gameObject = partyMenuButton->get_gameObject();
    HMUI::CurvedTextMeshPro *partyMenuText = gameObject->GetComponentInChildren<HMUI::CurvedTextMeshPro *>();

        if(getModConfig().PartyToggle.GetValue() == 0){
    partyMenuText->SetText("PARTY!");
    }
    else if(getModConfig().PartyToggle.GetValue() == 1){
    partyMenuText->SetText(getModConfig().PartyButton.GetValue());
    }
    else{
        getModConfig().PartyToggle.SetValue(0);
    }
}

  MAKE_HOOK_MATCH(MainMenuOnlineHook, &GlobalNamespace::MainMenuViewController::DidActivate, void, GlobalNamespace::MainMenuViewController
*self, bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling) {
    MainMenuOnlineHook(self, firstActivation, addedToHierarchy, screenSystemEnabling);

    UnityEngine::UI::Button *onlineMenuButton = self->dyn__multiplayerButton();
    UnityEngine::GameObject *gameObject = onlineMenuButton->get_gameObject();
    HMUI::CurvedTextMeshPro *onlineMenuText = gameObject->GetComponentInChildren<HMUI::CurvedTextMeshPro *>();

        if(getModConfig().OnlineToggle.GetValue() == 0){
    onlineMenuText->SetText("ONLINE!");
    }
    else if(getModConfig().OnlineToggle.GetValue() == 1){
    onlineMenuText->SetText(getModConfig().OnlineButton.GetValue());
    }
    else{
        getModConfig().OnlineToggle.SetValue(0);
    }
    }
  
    MAKE_HOOK_MATCH(MainMenuCampaignHook, &GlobalNamespace::MainMenuViewController::DidActivate, void, GlobalNamespace::MainMenuViewController
*self, bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling) {
    MainMenuCampaignHook(self, firstActivation, addedToHierarchy, screenSystemEnabling);

    UnityEngine::UI::Button *campaignMenuButton = self->dyn__campaignButton();
    UnityEngine::GameObject *gameObject = campaignMenuButton->get_gameObject();
    HMUI::CurvedTextMeshPro *campaignMenuText = gameObject->GetComponentInChildren<HMUI::CurvedTextMeshPro *>();

        if(getModConfig().CampaignToggle.GetValue() == 0){
    campaignMenuText->SetText("CAMPAIGN!");
    }
    else if(getModConfig().CampaignToggle.GetValue() == 1){
    campaignMenuText->SetText(getModConfig().CampaignButton.GetValue());
    }
    else{
        getModConfig().CampaignToggle.SetValue(0);
    }
}

MAKE_HOOK_MATCH(ResultsContinueHook, &GlobalNamespace::ResultsViewController::DidActivate, void, GlobalNamespace::ResultsViewController *self, bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling){
    ResultsContinueHook(self, firstActivation, addedToHierarchy, screenSystemEnabling);

    UnityEngine::UI::Button *continueResultsButton = self->dyn__continueButton();
    UnityEngine::GameObject *gameObject = continueResultsButton->get_gameObject();
    HMUI::CurvedTextMeshPro * continueResultsText = gameObject->GetComponentInChildren<HMUI::CurvedTextMeshPro *>();

    continueResultsText->SetText("L bozo");
}

void DidActivate(HMUI::ViewController* self, bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling){
if(firstActivation){
UnityEngine::GameObject* container = BeatSaberUI::CreateScrollableSettingsContainer(self->get_transform());
BeatSaberUI::CreateUIButton(container->get_transform(), "Solo Toggle!",
[&](){
    getLogger().info("I was clicked");
    if(getModConfig().SoloToggle.GetValue() == 0){
    getModConfig().SoloToggle.SetValue(1);
    }
    else {
        getModConfig().SoloToggle.SetValue(0);
    }
});
BeatSaberUI::CreateUIButton(container->get_transform(), "Online Toggle!",
[&](){
    getLogger().info("I was clicked");
    if(getModConfig().OnlineToggle.GetValue() == 0){
    getModConfig().OnlineToggle.SetValue(1);
    }
    else {
        getModConfig().OnlineToggle.SetValue(0);
    }
});
BeatSaberUI::CreateUIButton(container->get_transform(), "Party Toggle!",
[&](){
    getLogger().info("I was clicked");
    if(getModConfig().PartyToggle.GetValue() == 0){
    getModConfig().PartyToggle.SetValue(1);
    }
    else {
        getModConfig().PartyToggle.SetValue(0);
    }
});
BeatSaberUI::CreateUIButton(container->get_transform(), "Campaign Toggle!",
[&](){
    getLogger().info("I was clicked");
    if(getModConfig().CampaignToggle.GetValue() == 0){
    getModConfig().CampaignToggle.SetValue(1);
    }
    else {
        getModConfig().CampaignToggle.SetValue(0);
    }
});
}
}

// Called later on in the game loading - a good time to install function hooks
extern "C" void load() {
    il2cpp_functions::Init();
    LoggerContextObject logger = getLogger().WithContext("load");
    getModConfig().Init(modInfo);
    QuestUI::Init();
    QuestUI::Register::RegisterModSettingsViewController(modInfo, DidActivate);
    QuestUI::Register::RegisterMainMenuModSettingsViewController(modInfo, DidActivate);
    getLogger().info("Bad menu initiated");

    getLogger().info("Installing hooks...");
    INSTALL_HOOK(getLogger(), MainMenuSoloHook);
    INSTALL_HOOK(getLogger(), MainMenuOnlineHook);
    INSTALL_HOOK(getLogger(), MainMenuPartyHook);
    INSTALL_HOOK(getLogger(), MainMenuCampaignHook);
    INSTALL_HOOK(getLogger(), ResultsContinueHook);
    getLogger().info("Installed all hooks!");
}