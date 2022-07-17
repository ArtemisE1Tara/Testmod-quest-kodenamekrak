#include "main.hpp"
#include "questui/shared/QuestUI.hpp"
#include "questui/shared/BeatSaberUI.hpp"
#include "config-utils/shared/config-utils.hpp"
#include "ModConfig.hpp"
#include "hooks.hpp"
using namespace GlobalNamespace;
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
    info.id = MOD_ID;
    info.version = VERSION;
    modInfo = info;
	
    getConfig().Load(); // Load the config file
    getLogger().info("Completed setup!");
}

void DidActivate(HMUI::ViewController* self, bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling){
if(firstActivation){
UnityEngine::GameObject* container = QuestUI::BeatSaberUI::CreateScrollableSettingsContainer(self->get_transform());

AddConfigValueToggle(container->get_transform(), getModConfig().NoteJumpSpeedEnabled)->get_gameObject();

            AddConfigValueIncrementFloat(container->get_transform(), getModConfig().NoteJumpSpeed, 0, 1.0f, 0.f, 50);


AddConfigValueToggle(container->get_transform(), getModConfig().RotationEnabled)->get_gameObject();

AddConfigValueIncrementFloat(container->get_transform(), getModConfig().RotationIncrement, 0, 5.0f, 0.f, 30);

QuestUI::BeatSaberUI::CreateUIButton(container->get_transform(), "", [&](){
    getModConfig().RotationIncrement.SetValue(0);
});
AddConfigValueIncrementFloat(container->get_transform(), getModConfig().ButtonXPos, 0, 5.0f, 0.f, 100);
AddConfigValueIncrementFloat(container->get_transform(), getModConfig().ButtonYPos, 0, 5.0f, 0.f, 100);
AddConfigValueIncrementFloat(container->get_transform(), getModConfig().ButtonXSize, 0, 5.0f, 0.f, 100);
AddConfigValueIncrementFloat(container->get_transform(), getModConfig().ButtonYSize, 0, 5.0f, 0.f, 100);

}
}

// Called later on in the game loading - a good time to install function hooks
extern "C" void load() {
    il2cpp_functions::Init();

    QuestUI::Init();
    QuestUI::Register::RegisterMainMenuModSettingsViewController(modInfo, DidActivate);
    QuestUI::Register::RegisterModSettingsViewController(modInfo, DidActivate);

    getLogger().info("Installing hooks...");

    getLogger().info("Installed all hooks!");
}