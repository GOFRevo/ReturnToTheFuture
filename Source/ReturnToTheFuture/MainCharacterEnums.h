#pragma once
#include "CoreMinimal.h"
#include "MainCharacterEnums.generated.h"

UENUM(BlueprintType)
enum class ECharacterMainState: uint8
{
	ECMS_OnSpaceShip UMETA(DisplayName = "OnSpaceShip"),
	ECMS_OnSpaceStation UMETA(DisplayName = "OnSpaceStation"),

	ECMS_MAX UMETA(DisplayName = "DefaultMax")
};
