// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/PlayerCameraManager.h"
#include "RTFCameraManager.generated.h"

/**
 * 
 */
UCLASS()
class RETURNTOTHEFUTURE_API ARTFCameraManager: public APlayerCameraManager
{
	GENERATED_BODY()
private:
	inline static ARTFCameraManager* InstancePointer = nullptr;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera Mesh", Meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* CameraBehavior;
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera Properties|SpaceShip", Meta = (AllowPrivateAccess = "true"))
	float SpaceShipCameraFOV;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera Properties|IT", Meta = (AllowPrivateAccess = "true"))
	float ITCameraFOV;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera Properties|IF", Meta = (AllowPrivateAccess = "true"))
	float IFCameraFOV;

	ARTFCameraManager();

	void CustomCamera(float DeltaTime, FMinimalViewInfo& ViewInfo);
	static ARTFCameraManager* GetInstance();

	void SpaceShipCustomCamera(float DeltaTime, FMinimalViewInfo& ViewInfo);
	void ITCutomCamera(float DeltaTime, FMinimalViewInfo& ViewInfo);
	void IFCutomCamera(float DeltaTime, FMinimalViewInfo& ViewInfo);
};
