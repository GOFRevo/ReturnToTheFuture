// Fill out your copyright notice in the Description page of Project Settings.


#include "SpaceShipCameraManager.h"
#include "MainSpaceShip.h"
#include "SpaceShipCameraAnimInstance.h"
#include "SpaceShipController.h"

ASpaceShipCameraManager::ASpaceShipCameraManager():
	MainSpaceShip(nullptr)
{
	CameraBehavior = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Camera Behavior"));
	CameraBehavior->SetupAttachment(RootComponent);
}

void ASpaceShipCameraManager::OnPosses(APawn* SpaceShip)
{
	MainSpaceShip = CastChecked<AMainSpaceShip>(SpaceShip);
	USpaceShipCameraAnimInstance* SpaceShipCameraAnimInstance =
		CastChecked<USpaceShipCameraAnimInstance>(CameraBehavior->GetAnimInstance());
	SpaceShipCameraAnimInstance->SpaceShipController =
		CastChecked<ASpaceShipController>(GetOwningPlayerController());
}

bool ASpaceShipCameraManager::CustomCamera(float DeltaTime, FMinimalViewInfo& ViewInfo)
{
	ViewInfo.Location = MainSpaceShip->GetActorLocation() - FVector{200, 0, -200};
	ViewInfo.Rotation = FRotator(-45.0, 0, 0);
	ViewInfo.FOV = CameraFOV;
	return true;
}


