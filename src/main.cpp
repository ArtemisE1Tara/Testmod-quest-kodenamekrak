#include "main.hpp"
#include "GlobalNamespace/MainMenuViewController.hpp"
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

MAKE_HOOK_MATCH(MainMenuUIHook, &GlobalNamespace::MainMenuViewController::DidActivate, void, GlobalNamespace::MainMenuViewController
*self, bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling) {
    MainMenuUIHook(self, firstActivation, addedToHierarchy, screenSystemEnabling);
    
    UnityEngine::UI::Button *soloMenuButton = self->dyn__soloButton();
    UnityEngine::GameObject *gameObject = soloMenuButton->get_gameObject();
    HMUI::CurvedTextMeshPro *soloMenuText = gameObject->GetComponentInChildren<HMUI::CurvedTextMeshPro *>();
    
    if(getModConfig().SoloToggle.GetValue() == 0){
    soloMenuText->SetText(getModConfig().SoloButton1.GetValue());
    }
    else if(getModConfig().SoloToggle.GetValue() == 1){
    soloMenuText->SetText(getModConfig().SoloButton2.GetValue());
    }
    else{
        getModConfig().SoloToggle.SetValue(1);
    }
}

void DidActivate(HMUI::ViewController* self, bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling){
if(firstActivation){
UnityEngine::GameObject* container = BeatSaberUI::CreateScrollableSettingsContainer(self->get_transform());
BeatSaberUI::CreateUIButton(container->get_transform(), "Click Me Daddy!",
[&](){
    getLogger().info("I was clicked");
    if(getModConfig().SoloToggle.GetValue() == 0){
    getModConfig().SoloToggle.SetValue(1);
    }
    else {
        getModConfig().SoloToggle.SetValue(0);
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
    INSTALL_HOOK(getLogger(), MainMenuUIHook);
    getLogger().info("Installed all hooks!");
}