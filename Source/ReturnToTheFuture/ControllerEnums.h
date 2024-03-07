#pragma once
#include "CoreMinimal.h"
#include "ControllerEnums.generated.h"

UENUM(BlueprintType)
enum class EControllerState: uint8
{
	ECS_SpaceShip UMETA(DisplayName = "SpaceShip"),
	ECS_IT UMETA(DisplayName = "IT"),
	ECS_IF UMETA(DisplayName = "IF"),
	ECS_OT UMETA(DisplayName = "OT"),

	EMG_MAX UMETA(DisplayName = "DefaultMax")
};

UENUM(BlueprintType)
enum class EMainCharacterState: uint8
{
	EMCS_OnSpaceShip UMETA(DisplayName = "OnSpaceShip"),
	EMCS_OnSpaceStation UMETA(DisplayName = "OnSpaceStation"),

	EMCS_MAX UMETA(DisplayName = "DefaultMax")
};
