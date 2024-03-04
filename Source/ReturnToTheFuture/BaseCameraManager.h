// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/PlayerCameraManager.h"
#include "BaseCameraManager.generated.h"

/**
 * 
 */
UCLASS()
class RETURNTOTHEFUTURE_API ABaseCameraManager : public APlayerCameraManager
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera Properties", Meta = (AllowPrivateAccess = "true"))
	float CameraFOV;

	ABaseCameraManager();
	
	virtual bool CustomCamera(float DeltaTime, FMinimalViewInfo& ViewInfo);
	
};
