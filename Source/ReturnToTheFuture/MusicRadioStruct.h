#pragma once
#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "MusicRadioEnums.h"
#include "MusicRadioStruct.generated.h"

USTRUCT(BlueprintType)
struct FMusicRadioInfo: public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bIsOpened = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	EMusicRadioState MusicRadioState = EMusicRadioState::EMRS_Invalid;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FString ChannelName;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FString MusicName;
};
