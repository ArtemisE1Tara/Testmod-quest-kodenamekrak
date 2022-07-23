#pragma once

#include "config-utils/shared/config-utils.hpp"


DECLARE_CONFIG(ModConfig,
    CONFIG_VALUE(NoteJumpSpeed, float, "Note Jump Speed", 1.0f);
    CONFIG_VALUE(NoteJumpSpeedEnabled, bool, "Enable custom note jump speed", false);
    CONFIG_VALUE(Clicked, int, "Clicked", 0);
    CONFIG_VALUE(RotationEnabled, bool, "Enable Rotation", false);
    CONFIG_VALUE(RotationIncrement, float, "Rotation Increment", 0.0f);
    CONFIG_VALUE(Test, std::string, "Test", "TEST!");
    CONFIG_VALUE(SwapColours, bool, "A jank colour swap", false);
    CONFIG_VALUE(ScreenTextChanger, bool, "Respawns the screen ", false);
    CONFIG_VALUE(NJSTEST, float, "NJSTEST", 0.0f);

    CONFIG_INIT_FUNCTION(
        CONFIG_INIT_VALUE(NoteJumpSpeed);
        CONFIG_INIT_VALUE(NoteJumpSpeedEnabled);
        CONFIG_INIT_VALUE(Clicked);
        CONFIG_INIT_VALUE(RotationEnabled);
        CONFIG_INIT_VALUE(RotationIncrement);
        CONFIG_INIT_VALUE(Test);
        CONFIG_INIT_VALUE(SwapColours);
        CONFIG_INIT_VALUE(ScreenTextChanger);
        CONFIG_INIT_VALUE(NJSTEST);

    )
)