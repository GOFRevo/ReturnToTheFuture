#pragma once
#include "CoreMinimal.h"
#include "CameraEnums.generated.h"

UENUM(BlueprintType)
enum class ECameraViewState: uint8
{
	ECVS_SpaceShipView UMETA(DisplayName = "SpaceShipView"),
	ECVS_ITView UMETA(DisplayName = "ITView"),
	ECVS_IFView UMETA(DisplayName = "IFView"),
	ECVS_OTView UMETA(DisplayName = "OTView"),
	ECVS_EmptyView UMETA(DisplayName = "EmptyView"),

	ECVS_MAX UMETA(DisplayName = "DefaultMax")
};
