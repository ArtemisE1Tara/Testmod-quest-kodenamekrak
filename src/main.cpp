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
#include "GlobalNamespace/GameplaySetupViewController.hpp"
#include "GlobalNamespace/BeatmapObjectSpawnMovementData.hpp"
#include "GlobalNamespace/BeatmapObjectSpawnMovementData_NoteJumpValueType.hpp"
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

/*AKE_HOOK_MATCH(SoloFreeplayButtons, &GlobalNamespace::GameplaySetupViewController::DidActivate, void, GlobalNamespace::GameplaySetupViewController *self, bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling)
{
    SoloFreeplayButtons(self, firstActivation, addedToHierarchy, screenSystemEnabling);
    if (firstActivation)
    {
        getLogger().info("Creating UI button");
    QuestUI::BeatSaberUI::CreateUIButton(self->get_transform(), "Test", UnityEngine::Vector2(150.0f, 20.0f), UnityEngine::Vector2(20.0f, 20.0f), [&]() {
        getModConfig().Clicked.SetValue(getModConfig().Clicked.GetValue() + 1);
 });
 }
}*/

MAKE_HOOK_MATCH(BeatmapObjectSpawnMovementData_Init, &BeatmapObjectSpawnMovementData::Init,
        void, BeatmapObjectSpawnMovementData* self, int noteLinesCount, float startNoteJumpMovementSpeed, float startBpm, BeatmapObjectSpawnMovementData::NoteJumpValueType noteJumpValueType, float noteJumpValue, IJumpOffsetYProvider* jumpOffsetYProvider, UnityEngine::Vector3 rightVec, UnityEngine::Vector3 forwardVec) {
            if(getModConfig().NoteJumpSpeedEnabled.GetValue() == true){
            startNoteJumpMovementSpeed = getModConfig().NoteJumpSpeed.GetValue();
            }
            else{
              BeatmapObjectSpawnMovementData_Init(self, noteLinesCount, startNoteJumpMovementSpeed, startBpm, noteJumpValueType, noteJumpValue, jumpOffsetYProvider, rightVec, forwardVec);
            }

    BeatmapObjectSpawnMovementData_Init(self, noteLinesCount, startNoteJumpMovementSpeed, startBpm, noteJumpValueType, noteJumpValue, jumpOffsetYProvider, rightVec, forwardVec);
}
MAKE_HOOK_MATCH(GameplaySetupViewController, &GameplaySetupViewController::DidActivate, void, GlobalNamespace::GameplaySetupViewController *self, bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling){
    GameplaySetupViewController(self, firstActivation, addedToHierarchy, screenSystemEnabling);
}

void DidActivate(HMUI::ViewController* self, bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling){
if(firstActivation){
UnityEngine::GameObject* container = BeatSaberUI::CreateScrollableSettingsContainer(self->get_transform());
 QuestUI::BeatSaberUI::CreateToggle(container->get_transform(), "Is Enabled", getModConfig().NoteJumpSpeedEnabled.GetValue(),
     [](bool value) {  
    getModConfig().NoteJumpSpeedEnabled.SetValue(value);
                }
            );
AddConfigValueIncrementFloat(container->get_transform(), getModConfig().NoteJumpSpeed, 0, 1.0f, 0.f, 50);
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
    QuestUI::Register::RegisterGameplaySetupMenu(modInfo, QuestUI::Register::MenuType::All);
    getLogger().info("Bad menu initiated");

    getLogger().info("Installing hooks...");
    INSTALL_HOOK(getLogger(), BeatmapObjectSpawnMovementData_Init);
    //INSTALL_HOOK(getLogger(), SoloFreeplayButtons);
    getLogger().info("Installed all hooks!");
}