#pragma once

#include "config-utils/shared/config-utils.hpp"


DECLARE_CONFIG(ModConfig,
    CONFIG_VALUE(SoloToggle, int, "Solo Toggle", 0);
    CONFIG_VALUE(SoloButton1, std::string, "Solo Button1", "Four big guys");
    CONFIG_VALUE(SoloButton2, std::string, "Solo Button2", "And they bust in my eyes");

    CONFIG_INIT_FUNCTION(
        CONFIG_INIT_VALUE(SoloToggle);
        CONFIG_INIT_VALUE(SoloButton1);
        CONFIG_INIT_VALUE(SoloButton2);
    )
)