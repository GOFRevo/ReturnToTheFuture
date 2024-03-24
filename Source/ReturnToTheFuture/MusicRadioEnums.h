#pragma once
#include "CoreMinimal.h"
#include "MusicRadioEnums.generated.h"

UENUM(BlueprintType)
enum class EMusicDataState: uint8
{
	EMDS_IsPlaying UMETA(DisplayName = "IsPlaying"),
	EMDS_IsStopping UMETA(DisplayName = "IsStopping"),
	EMDS_IsLoading UMETA(DisplayName = "IsLoading"),
	EMDS_HasComplete UMETA(DisplayName = "HasComplete"),

	EMDS_MAX UMETA(DisplayName = "DefaultMax")
};
UENUM(BlueprintType)
enum class EMusicRadioState: uint8
{
	EMRS_Opened UMETA(DisplayName = "Opened"),
	EMRS_Closed UMETA(DisplayName = "Closed"),

	EMRS_MAX UMETA(DisplayName = "DefaultMax")
};
