#pragma once

#include "config-utils/shared/config-utils.hpp"


DECLARE_CONFIG(ModConfig,
    CONFIG_VALUE(SoloToggle, int, "Solo Toggle", 0);
    CONFIG_VALUE(SoloButton, std::string, "Solo Button", "SOLO!");
    CONFIG_VALUE(OnlineToggle, int, "Online Toggle", 0);
    CONFIG_VALUE(OnlineButton, std::string, "Online Button", "ONLINE!");
    CONFIG_VALUE(PartyToggle, int, "Party Toggle", 0);
    CONFIG_VALUE(PartyButton, std::string, "Party Button", "PARTY!");
    CONFIG_VALUE(CampaignToggle, int, "Campaign Toggle", 0);
    CONFIG_VALUE(CampaignButton, std::string, "Campaign Button", "CAMPAIGN!");

    CONFIG_INIT_FUNCTION(
        CONFIG_INIT_VALUE(SoloToggle);
        CONFIG_INIT_VALUE(SoloButton);
        CONFIG_INIT_VALUE(OnlineToggle);
        CONFIG_INIT_VALUE(OnlineButton);
        CONFIG_INIT_VALUE(PartyToggle);
        CONFIG_INIT_VALUE(PartyButton);
        CONFIG_INIT_VALUE(CampaignToggle);
        CONFIG_INIT_VALUE(CampaignButton);
    )
)