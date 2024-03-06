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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera Properties", Meta = (AllowPrivateAccess = "true"))
	float CameraFOV;

	ARTFCameraManager();

	void CustomCamera(float DeltaTime, FMinimalViewInfo& ViewInfo);
	static ARTFCameraManager* GetInstance();
};
