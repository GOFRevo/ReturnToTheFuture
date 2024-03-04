// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BaseCameraManager.h"
#include "SpaceShipCameraManager.generated.h"

/**
 * 
 */
UCLASS()
class RETURNTOTHEFUTURE_API ASpaceShipCameraManager : public ABaseCameraManager
{
	GENERATED_BODY()
private:
	UPROPERTY()
	class AMainSpaceShip* MainSpaceShip;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera Mesh", Meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* CameraBehavior;
public:
	ASpaceShipCameraManager();
	virtual void OnPosses(APawn* SpaceShip);
	
	virtual bool CustomCamera(float DeltaTime, FMinimalViewInfo& ViewInfo) override;
	
};
