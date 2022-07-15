#pragma once

#include "config-utils/shared/config-utils.hpp"


DECLARE_CONFIG(ModConfig,
    CONFIG_VALUE(NoteJumpSpeed, float, "NoteJumpSpeed", 1);
    CONFIG_VALUE(NoteJumpSpeedEnabled, bool, "NoteJumpSpeedEnabled", false)
    CONFIG_VALUE(Clicked, int, "Clicked", 0)

    CONFIG_INIT_FUNCTION(
        CONFIG_INIT_VALUE(NoteJumpSpeed);
        CONFIG_INIT_VALUE(NoteJumpSpeedEnabled);
        CONFIG_INIT_VALUE(Clicked);
    )
)