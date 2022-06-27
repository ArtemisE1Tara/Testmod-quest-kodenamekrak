#include "main.hpp"
#include "GlobalNamespace/MainMenuViewController.hpp"
#include "UnityEngine/UI/Button.hpp"
#include "UnityEngine/GameObject.hpp"
#include "HMUI/CurvedTextMeshPro.hpp"
#include "beatsaber-hook/shared/utils/hooking.hpp"
#include "questui/shared/QuestUI.hpp"
#include "questui/shared/BeatSaberUI.hpp"
using namespace GlobalNamespace;
using namespace QuestUI;

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
    // Run the original method before our code.
    // Note, you can run the original method after our code if you want to change arguments.
    MainMenuUIHook(self, firstActivation, addedToHierarchy, screenSystemEnabling);

    // Get the _soloButton text using the dyn_ method and simple unity jazz. dyn_ safely get 
    // fields and shouldn't change much during updates.
    
    UnityEngine::UI::Button *soloMenuButton = self->dyn__soloButton();
    UnityEngine::GameObject *gameObject = soloMenuButton->get_gameObject();
    HMUI::CurvedTextMeshPro *soloMenuText = gameObject->GetComponentInChildren<HMUI::CurvedTextMeshPro *>();
    
    // Set the text to "Skill Issue"
    soloMenuText->SetText("Skill Issue");
}

void DidActivate(HMUI::ViewController* self, bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling){
if(firstActivation){
UnityEngine::GameObject* container = BeatSaberUI::CreateScrollableSettingsContainer(self->get_transform());
BeatSaberUI::CreateUIButton(container->get_transform(), "Click Me Daddy!",
[&](){
    getLogger().info("I was clicked");
});
}
}

// Called later on in the game loading - a good time to install function hooks
extern "C" void load() {
    il2cpp_functions::Init();
    LoggerContextObject logger = getLogger().WithContext("load");

QuestUI::Init();
QuestUI::Register::RegisterModSettingsViewController(modInfo, DidActivate);
QuestUI::Register::RegisterMainMenuModSettingsViewController(modInfo, DidActivate);
getLogger().info("Bad menu initiated");

    getLogger().info("Installing hooks...");
    INSTALL_HOOK(getLogger(), MainMenuUIHook);
    getLogger().info("Installed all hooks!");
}