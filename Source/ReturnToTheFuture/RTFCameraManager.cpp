// Fill out your copyright notice in the Description page of Project Settings.


#include "RTFCameraManager.h"
#include "RTFController.h"
#include "MainCharacter.h"
#include "MainSpaceShip.h"

ARTFCameraManager::ARTFCameraManager():
	SpaceShipCameraFOV(90.0f),
	ITCameraFOV(90.0f),
	IFCameraFOV(90.0f),
	OTCameraFOV(90.0f)
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
	switch(ARTFController::GetInstance()->GetControllerState())
	{
	case EControllerState::ECS_SpaceShip:
		SpaceShipCustomCamera(DeltaTime, ViewInfo);
		break;
	case EControllerState::ECS_IT:
		ITCustomCamera(DeltaTime, ViewInfo);
		break;
	case EControllerState::ECS_IF:
		IFCustomCamera(DeltaTime, ViewInfo);
		break;
	case EControllerState::ECS_OT:
		OTCustomCamera(DeltaTime, ViewInfo);
		break;
	default:
		check(false);
	}
}

void ARTFCameraManager::SpaceShipCustomCamera(float DeltaTime, FMinimalViewInfo& ViewInfo)
{
	const ARTFController* RTFController = ARTFController::GetInstance();
	ViewInfo.FOV = SpaceShipCameraFOV;
	ViewInfo.Location = RTFController->GetMainSpaceShip()->GetActorLocation() + FVector{-200.0f, 0.0f, 200.0f};
	ViewInfo.Rotation = RTFController->GetControlRotation();
}

void ARTFCameraManager::ITCustomCamera(float DeltaTime, FMinimalViewInfo& ViewInfo)
{
	const ARTFController* RTFController = ARTFController::GetInstance();
	ViewInfo.FOV = ITCameraFOV;
	ViewInfo.Location = RTFController->GetMainCharacter()->GetActorLocation() + FVector{-200.0f, 0.0f, 0.0f};
	ViewInfo.Rotation = RTFController->GetControlRotation();
}

void ARTFCameraManager::IFCustomCamera(float DeltaTime, FMinimalViewInfo& ViewInfo)
{
	const ARTFController* RTFController = ARTFController::GetInstance();
	ViewInfo.FOV = IFCameraFOV;
	ViewInfo.Location = RTFController->GetMainCharacter()->GetActorLocation();
	ViewInfo.Rotation = RTFController->GetControlRotation();
}

void ARTFCameraManager::OTCustomCamera(float DeltaTime, FMinimalViewInfo& ViewInfo)
{
	const ARTFController* RTFController = ARTFController::GetInstance();
	ViewInfo.FOV = OTCameraFOV;
	ViewInfo.Location = RTFController->GetMainCharacter()->GetActorLocation() + FVector{-100.0f, 0.0f, 100.0f};
	ViewInfo.Rotation = RTFController->GetControlRotation();
}
