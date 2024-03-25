#pragma once
#include "CoreMinimal.h"
#include "MusicRadioEnums.generated.h"

UENUM(BlueprintType)
enum class EMusicDataState: uint8
{
	EMDS_InValid UMETA(DisplayName = "Invalid"),
	EMDS_Playing UMETA(DisplayName = "Playing"),
	EMDS_Paused UMETA(DisplayName = "Pasued"),
	EMDS_Stopped UMETA(DisplayName = "Stopped"),
	EMDS_Loading UMETA(DisplayName = "Loading"),
	EMDS_LoadComplete UMETA(DisplayName = "LoadComplete"),
	EMDS_PlayComplete UMETA(DisplayName = "PlayComplete"),

	EMDS_MAX UMETA(DisplayName = "DefaultMax")
};

UENUM(BlueprintType)
enum class EMusicRadioState: uint8
{
	EMRS_Invalid UMETA(DisplayName = "Invalid"),
	EMRS_Playing UMETA(DisplayName = "Playing"),
	EMRS_Paused UMETA(DisplayName = "Paused"),
	EMRS_Loading UMETA(DisplayName = "Loading"),

	EMRS_MAX UMETA(DisplayName = "DefaultMax")
};
