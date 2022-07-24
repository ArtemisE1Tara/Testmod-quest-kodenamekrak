#include "main.hpp"
#include "questui/shared/QuestUI.hpp"
#include "questui/shared/BeatSaberUI.hpp"
#include "config-utils/shared/config-utils.hpp"
#include "ModConfig.hpp"
#include "hooks.hpp"
#include "HMUI/ViewController.hpp"
#include "UnityEngine/UI/LayoutElement.hpp"

using namespace GlobalNamespace;
DEFINE_CONFIG(ModConfig);
float scale = 0.2f;

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


void DidActivate(HMUI::ViewController* self, bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling) {
    // Create our UI elements only when shown for the first time.
    if(firstActivation) {

        UnityEngine::GameObject* container = QuestUI::BeatSaberUI::CreateScrollableSettingsContainer(self->get_transform());

        AddConfigValueToggle(container->get_transform(), getModConfig().NoteJumpSpeedEnabled);
        AddConfigValueIncrementFloat(container->get_transform(), getModConfig().NoteJumpSpeed, 0, 1.0f, -50.0f, 50.0f);

        AddConfigValueToggle(container->get_transform(), getModConfig().RotationEnabled);
        AddConfigValueIncrementFloat(container->get_transform(), getModConfig().RotationIncrement, 0, 5.0f, -180.0f, 180.0f);

        QuestUI::BeatSaberUI::AddHoverHint(AddConfigValueToggle(container->get_transform(), getModConfig().SwapColours)->get_gameObject(), "Overrides Other stuff");


        UnityEngine::GameObject* Corner1 = QuestUI::BeatSaberUI::CreateFloatingScreen(UnityEngine::Vector2(100.0f * getModConfig().Scale.GetValue() , 1.0f), UnityEngine::Vector3(0 , 1.0f, 1.0f * getModConfig().Scale.GetValue()), UnityEngine::Vector3(0, 0, 0), 0.0f, false, true, 3);
        UnityEngine::GameObject* Corner2 = QuestUI::BeatSaberUI::CreateFloatingScreen(UnityEngine::Vector2(100.0f * getModConfig().Scale.GetValue() , 1.0f), UnityEngine::Vector3(0 , 1.0f, -1.0f * getModConfig().Scale.GetValue()), UnityEngine::Vector3(0, 0, 0), 0.0f, false, true, 3);
        UnityEngine::GameObject* Corner3 = QuestUI::BeatSaberUI::CreateFloatingScreen(UnityEngine::Vector2(100.0f * 0.6666f * getModConfig().Scale.GetValue(), 1.0f), UnityEngine::Vector3(1.5f * getModConfig().Scale.GetValue(), 1.0f, 0), UnityEngine::Vector3(0, 90, 0), 0.0f, false, true, 3);
        UnityEngine::GameObject* Corner4 = QuestUI::BeatSaberUI::CreateFloatingScreen(UnityEngine::Vector2(100.0f * 0.6666f * getModConfig().Scale.GetValue(), 1.0f), UnityEngine::Vector3(-1.5f * getModConfig().Scale.GetValue(), 1.0f, 0), UnityEngine::Vector3(0, 90, 0), 0.0f, false, true, 3);
        AddConfigValueIncrementFloat(container->get_transform(), getModConfig().Scale, 1, 0.1f, 0.1f, 1.5f);
        QuestUI::BeatSaberUI::CreateUIButton(container->get_transform(), "test", [&](){
            UnityEngine::Transform* Screen = Corner1->get_transform();
            Screen->set_position(UnityEngine::Vector3(0, 0, 0));
        });


        UnityEngine::Transform* parent = container->get_transform();
        auto layout = QuestUI::BeatSaberUI::CreateHorizontalLayoutGroup(parent);  layout->GetComponent<UnityEngine::UI::LayoutElement*>()->set_preferredWidth(60.0f); 
        layout->set_childControlWidth(true); 
        auto layoutParent = layout->get_transform();

        auto stringSetting = AddConfigValueStringSetting(layoutParent, getModConfig().Test);

    }
}

// Called later on in the game loading - a good time to install function hooks
extern "C" void load() {
    il2cpp_functions::Init();

    QuestUI::Init();
    QuestUI::Register::RegisterMainMenuModSettingsViewController(modInfo, DidActivate);
    QuestUI::Register::RegisterModSettingsViewController(modInfo, DidActivate);

    il2cpp_functions::Init();

    getModConfig().Init(modInfo);

    getLogger().info("Installing hooks...");

    auto& logger = getLogger();
    Hooks::InstallHooks(logger);

    getLogger().info("Installed all hooks!");
}