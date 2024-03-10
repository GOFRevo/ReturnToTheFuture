#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "CameraStruct.generated.h"

USTRUCT(BlueprintType)
struct FCameraMovementInfo: public FTableRowBase
{
	GENERATED_BODY()
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FRotator TargetCameraRotation;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FVector TargetCameraLocation;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FVector PivotLocation;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FTransform SmoothedPivotTarget;
};