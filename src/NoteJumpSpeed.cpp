#include "hooks.hpp"
#include "GlobalNamespace/BeatmapObjectSpawnMovementData.hpp"
#include "GlobalNamespace/BeatmapObjectSpawnMovementData_NoteJumpValueType.hpp"
#include "UnityEngine/Vector3.hpp"
#include "ModConfig.hpp"
#include "config-utils/shared/config-utils.hpp"
#include "GlobalNamespace/IDifficultyBeatmap.hpp"
#include "GlobalNamespace/ResultsViewController.hpp"
#include "GlobalNamespace/IBeatmapLevel.hpp"
#include "GlobalNamespace/BeatmapDifficulty.hpp"
#include "GlobalNamespace/BeatmapCharacteristicSO.hpp"
#include "GlobalNamespace/PlayerData.hpp"
#include "GlobalNamespace/IDifficultyBeatmap.hpp"
#include "GlobalNamespace/StandardLevelDetailView.hpp"
#include "beatsaber-hook/shared/utils/logging.hpp"
#include "GlobalNamespace/LevelScenesTransitionSetupDataSO.hpp"
#include "GlobalNamespace/GameplayCoreSceneSetupData.hpp"



bool GotNJS = false;
float NJS;
float practiceSpeed = 1;

using namespace GlobalNamespace;
IDifficultyBeatmap* currentBeatmap = nullptr;
#include "custom-types/shared/register.hpp"



MAKE_AUTO_HOOK_MATCH(BeatmapObjectSpawnMovementData_Init, &BeatmapObjectSpawnMovementData::Init,
        void, BeatmapObjectSpawnMovementData* self, int noteLinesCount, float startNoteJumpMovementSpeed, float startBpm, BeatmapObjectSpawnMovementData::NoteJumpValueType noteJumpValueType, float noteJumpValue, IJumpOffsetYProvider* jumpOffsetYProvider, UnityEngine::Vector3 rightVec, UnityEngine::Vector3 forwardVec) {

          if(getModConfig().SwapColours.GetValue()){
            if(GotNJS){
               startNoteJumpMovementSpeed = getModConfig().NJSTEST.GetValue() * 3;
            }
          }
          
            if(getModConfig().NoteJumpSpeedEnabled.GetValue() && !getModConfig().SwapColours.GetValue()){
            startNoteJumpMovementSpeed = getModConfig().NoteJumpSpeed.GetValue();
            } 
              BeatmapObjectSpawnMovementData_Init(self, noteLinesCount, startNoteJumpMovementSpeed, startBpm, noteJumpValueType, noteJumpValue, jumpOffsetYProvider, rightVec, forwardVec);

              BeatmapObjectSpawnMovementData_Init(self, noteLinesCount, startNoteJumpMovementSpeed, startBpm, noteJumpValueType, noteJumpValue, jumpOffsetYProvider, rightVec, forwardVec);
      
        }


        void UpdateLevel(IDifficultyBeatmap* beatmap, bool forceSet = false) {
    if(currentBeatmap == beatmap && !forceSet)
        return;
    currentBeatmap = beatmap;

        getModConfig().NJSTEST.SetValue(beatmap->get_noteJumpMovementSpeed());

        GotNJS = true;

  
}

MAKE_AUTO_HOOK_MATCH(NJSResetter, &ResultsViewController::DidActivate, void, ResultsViewController* self, bool firstActivation, bool addedToHeirarchy, bool screenSystemEnabling){
          if(firstActivation){
            getModConfig().NJSTEST.SetValue(0);
            GotNJS = false;
          }
        }


        MAKE_HOOK_MATCH(StandardLevelDetailView_RefreshContent, &StandardLevelDetailView::RefreshContent, void, StandardLevelDetailView* self) {
    StandardLevelDetailView_RefreshContent(self);

    UpdateLevel(self->selectedDifficultyBeatmap);
}

    