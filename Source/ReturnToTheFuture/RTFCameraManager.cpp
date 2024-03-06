// Fill out your copyright notice in the Description page of Project Settings.


#include "RTFCameraManager.h"
#include "RTFController.h"
#include "MainCharacter.h"
#include "MainSpaceShip.h"

ARTFCameraManager::ARTFCameraManager():
	CameraFOV(90.0f)
{
	InstancePointer = this;
	CameraBehavior = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Camera Behavior"));
	CameraBehavior->SetupAttachment(RootComponent);
}

ARTFCameraManager* ARTFCameraManager::GetInstance()
{
	return InstancePointer;
}

void ARTFCameraManager::CustomCamera(float DeltaTime, FMinimalViewInfo& ViewInfo)
{
	const ARTFController* RTFController = ARTFController::GetInstance();
	switch(RTFController->GetControllerState())
	{
	case EControllerState::ECS_SpaceShip:
		ViewInfo.FOV = CameraFOV;
		ViewInfo.Location = RTFController->GetMainSpaceShip()->GetActorLocation() + FVector{-100.0f, 0.0f, 100.0f};
		ViewInfo.Rotation = FRotator{-45.0f, 0.0f, 0.0f};
		break;
	case EControllerState::ECS_IT:
		ViewInfo.FOV = CameraFOV;
		ViewInfo.Location = RTFController->GetMainCharacter()->GetActorLocation() + FVector{-100.0f, 0.0f, 100.0f};
		ViewInfo.Rotation = FRotator{0.0f, 0.0f, 0.0f};
		break;
	case EControllerState::ECS_IF:
		break;
	case EControllerState::ECS_OT:
		break;
	default:
		check(false);
	}
	
}

