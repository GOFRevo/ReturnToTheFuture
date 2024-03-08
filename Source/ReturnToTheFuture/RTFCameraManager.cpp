// Fill out your copyright notice in the Description page of Project Settings.


#include "RTFCameraManager.h"
#include "RTFController.h"
#include "MainCharacter.h"
#include "MainSpaceShip.h"
#include "RTFCameraAnimInstance.h"

ARTFCameraManager::ARTFCameraManager():
	CameraViewState(ECameraViewState::ECVS_ITView),
	RTFCameraAnimInstance(nullptr),
	TargetCameraRotation(0.0f),
	TargetCameraLocation(0.0f),
	PivotLocation(0.0f)
{
	InstancePointer = this;
	CameraBehavior = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Camera Behavior"));
	CameraBehavior->SetupAttachment(RootComponent);
}

ARTFCameraManager* ARTFCameraManager::GetInstance()
{
	return InstancePointer;
}

void ARTFCameraManager::BeginPlay()
{
	Super::BeginPlay();
	RTFCameraAnimInstance = CastChecked<URTFCameraAnimInstance>(CameraBehavior->GetAnimInstance());
}

ECameraViewState ARTFCameraManager::GetCameraViewState() const
{
	return CameraViewState;
}

void ARTFCameraManager::SetCameraViewState(ECameraViewState NewViewState)
{
	CameraViewState = NewViewState;
}

void ARTFCameraManager::CustomCamera(float DeltaTime, FMinimalViewInfo& ViewInfo)
{
	switch(GetCameraViewState())
	{
	case ECameraViewState::ECVS_SpaceShipView:
		SpaceShipCustomCamera(DeltaTime, ViewInfo);
		break;
	case ECameraViewState::ECVS_ITView:
		ITCustomCamera(DeltaTime, ViewInfo);
		break;
	case ECameraViewState::ECVS_IFView:
		IFCustomCamera(DeltaTime, ViewInfo);
		break;
	case ECameraViewState::ECVS_OTView:
		OTCustomCamera(DeltaTime, ViewInfo);
		break;
	default:
		check(false);
	}
}

void ARTFCameraManager::SpaceShipCustomCamera(float DeltaTime, FMinimalViewInfo& ViewInfo)
{
	RTFCameraAnimInstance->UpdateSpaceShipInfo();
	const ARTFController* RTFController = ARTFController::GetInstance();
	const AMainSpaceShip* MainSpaceShip = RTFController->GetMainSpaceShip();
	ViewInfo.FOV = MainSpaceShip->SpaceShipCameraFOV;
	ViewInfo.Location = MainSpaceShip->GetActorLocation() + FVector{-200.0f, 0.0f, 200.0f};
	ViewInfo.Rotation = RTFController->GetControlRotation();
}

void ARTFCameraManager::ITCustomCamera(float DeltaTime, FMinimalViewInfo& ViewInfo)
{
	const ARTFController* RTFController = ARTFController::GetInstance();
	const AMainCharacter* MainCharacter = RTFController->GetMainCharacter();
	ViewInfo.FOV = MainCharacter->ITCameraFOV;
	ViewInfo.Location = RTFController->GetMainCharacter()->GetActorLocation() + FVector{-200.0f, 0.0f, 0.0f};
	ViewInfo.Rotation = RTFController->GetControlRotation();
}

void ARTFCameraManager::IFCustomCamera(float DeltaTime, FMinimalViewInfo& ViewInfo)
{
	const ARTFController* RTFController = ARTFController::GetInstance();
	const AMainCharacter* MainCharacter = RTFController->GetMainCharacter();
	ViewInfo.FOV = MainCharacter->IFCameraFOV;
	ViewInfo.Location = MainCharacter->GetActorLocation();
	ViewInfo.Rotation = RTFController->GetControlRotation();
}

void ARTFCameraManager::OTCustomCamera(float DeltaTime, FMinimalViewInfo& ViewInfo)
{
	const ARTFController* RTFController = ARTFController::GetInstance();
	const AMainCharacter* MainCharacter = RTFController->GetMainCharacter();
	ViewInfo.FOV = MainCharacter->OTCameraFOV;
	ViewInfo.Location = MainCharacter->GetActorLocation() + FVector{-100.0f, 0.0f, 100.0f};
	ViewInfo.Rotation = RTFController->GetControlRotation();
}

void ARTFCameraManager::ToSpaceShipView()
{
	SetCameraViewState(ECameraViewState::ECVS_SpaceShipView);
}

void ARTFCameraManager::ToITView()
{
	SetCameraViewState(ECameraViewState::ECVS_ITView);
}

void ARTFCameraManager::ToIFView()
{
	SetCameraViewState(ECameraViewState::ECVS_IFView);
}

void ARTFCameraManager::ToOTView()
{
	SetCameraViewState(ECameraViewState::ECVS_OTView);
}

float ARTFCameraManager::GetCameraBehaviorParam(const FName& CurveName) const
{
	if(RTFCameraAnimInstance == nullptr) return 0.0f;
	return RTFCameraAnimInstance->GetCurveValue(CurveName);
}

bool ARTFCameraManager::CanChangeCameraViewState(ECameraViewState NewState) const
{
	return CameraViewState != NewState && CameraViewState != ECameraViewState::ECVS_EmptyView;
}

