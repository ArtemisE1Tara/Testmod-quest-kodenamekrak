#pragma once

#include "config-utils/shared/config-utils.hpp"


DECLARE_CONFIG(ModConfig,
    CONFIG_VALUE(NoteJumpSpeed, float, "Note Jump Speed", 1.0f);
    CONFIG_VALUE(NoteJumpSpeedEnabled, bool, "Enable custom note jump speed", false);
    CONFIG_VALUE(Clicked, int, "Clicked", 0);
    CONFIG_VALUE(RotationEnabled, bool, "Enable Rotation", false);
    CONFIG_VALUE(RotationIncrement, float, "Rotation Increment", 0.0f);
    CONFIG_VALUE(ButtonXPos, float, "X position", 0.0f);
    CONFIG_VALUE(ButtonYPos, float, "Y position", 0.0f);
    CONFIG_VALUE(ButtonXSize, float, "Width", 10.0f);
    CONFIG_VALUE(ButtonYSize, float, "Height", 10.0f);



    CONFIG_INIT_FUNCTION(
        CONFIG_INIT_VALUE(NoteJumpSpeed);
        CONFIG_INIT_VALUE(NoteJumpSpeedEnabled);
        CONFIG_INIT_VALUE(Clicked);
        CONFIG_INIT_VALUE(RotationEnabled);
        CONFIG_INIT_VALUE(RotationIncrement);
        CONFIG_INIT_VALUE(ButtonXPos);
        CONFIG_INIT_VALUE(ButtonYPos);
        CONFIG_INIT_VALUE(ButtonXSize);
        CONFIG_INIT_VALUE(ButtonYSize);

    )
)