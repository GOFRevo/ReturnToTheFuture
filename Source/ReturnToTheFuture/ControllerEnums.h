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
	ECS_Idle UMETA(DisplayName = "Idle"),

	ECS_MAX UMETA(DisplayName = "DefaultMax")
};