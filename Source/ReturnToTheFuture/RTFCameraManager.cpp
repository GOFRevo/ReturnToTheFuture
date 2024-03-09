// Fill out your copyright notice in the Description page of Project Settings.


#include "RTFCameraManager.h"
#include "RTFController.h"
#include "MainCharacter.h"
#include "MainSpaceShip.h"
#include "RTFCameraAnimInstance.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"

ARTFCameraManager::ARTFCameraManager():
	CameraViewState(ECameraViewState::ECVS_ITView),
	RTFCameraAnimInstance(nullptr),
	TargetCameraRotation(0.0f),
	TargetCameraLocation(0.0f),
	PivotLocation(0.0f),
	SmoothedPivotTarget()
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

	const FTransform PivotTarget = MainSpaceShip->GetActorTransform();
	TargetCameraRotation = UKismetMathLibrary::RInterpTo(GetCameraRotation(),
			GetOwningPlayerController()->GetControlRotation(),
			DeltaTime, GetCameraBehaviorParam(FName("RotationLagSpeed")));
	const FVector Temp = CalculateAxisIndependentLag(SmoothedPivotTarget.GetLocation(), PivotTarget.GetLocation(), TargetCameraRotation,
		FVector(GetCameraBehaviorParam(FName("PivotLagSpeed_X")), GetCameraBehaviorParam(FName("PivotLagSpeed_Y")), GetCameraBehaviorParam(FName("PivotLagSpeed_Z"))), DeltaTime);
	SmoothedPivotTarget.SetLocation(Temp);
	SmoothedPivotTarget.SetRotation(PivotTarget.GetRotation());
	SmoothedPivotTarget.SetScale3D(FVector{1.0f, 1.0f, 1.0f});

	PivotLocation = SmoothedPivotTarget.GetLocation() +
			SmoothedPivotTarget.GetRotation().GetForwardVector() * GetCameraBehaviorParam(FName("PivotOffset_X")) +
			SmoothedPivotTarget.GetRotation().GetRightVector() * GetCameraBehaviorParam(FName("PivotOffset_Y")) +
			SmoothedPivotTarget.GetRotation().GetUpVector() * GetCameraBehaviorParam(FName("PivotOffset_Z"));

	TargetCameraLocation = PivotLocation +
			TargetCameraRotation.Quaternion().GetForwardVector() * GetCameraBehaviorParam(FName("CameraOffset_X")) +
			TargetCameraRotation.Quaternion().GetRightVector() * GetCameraBehaviorParam(FName("CameraOffset_Y")) +
			TargetCameraRotation.Quaternion().GetUpVector() * GetCameraBehaviorParam(FName("CameraOffset_Z"));

	// FHitResult HitResult;
	// UKismetSystemLibrary::SphereTraceSingle(this, MainSpaceShip->GetActorLocation(), TargetCameraLocation, 10.0f,
	//		UEngineTypes::ConvertToTraceType(ECollisionChannel::ECC_Visibility), false, TArray<AActor*>(),
	//		EDrawDebugTrace::Type::None, HitResult, true);
	// if(HitResult.bBlockingHit && !HitResult.bStartPenetrating)
	// {
	//	TargetCameraLocation += HitResult.Location - HitResult.TraceEnd;
	// }
	
	ViewInfo.Location = TargetCameraLocation;
	ViewInfo.Rotation = TargetCameraRotation;
	ViewInfo.FOV = MainSpaceShip->SpaceShipCameraFOV;
}

void ARTFCameraManager::ITCustomCamera(float DeltaTime, FMinimalViewInfo& ViewInfo)
{
	RTFCameraAnimInstance->UpdateITInfo();
	const ARTFController* RTFController = ARTFController::GetInstance();
	const AMainCharacter* MainCharacter = RTFController->GetMainCharacter();

	const FTransform PivotTarget = MainCharacter->GetActorTransform();
	TargetCameraRotation = UKismetMathLibrary::RInterpTo(GetCameraRotation(),
			GetOwningPlayerController()->GetControlRotation(),
			DeltaTime, GetCameraBehaviorParam(FName("RotationLagSpeed")));
	const FVector Temp = CalculateAxisIndependentLag(SmoothedPivotTarget.GetLocation(), PivotTarget.GetLocation(), TargetCameraRotation,
		FVector(GetCameraBehaviorParam(FName("PivotLagSpeed_X")), GetCameraBehaviorParam(FName("PivotLagSpeed_Y")), GetCameraBehaviorParam(FName("PivotLagSpeed_Z"))), DeltaTime);
	SmoothedPivotTarget.SetLocation(Temp);
	SmoothedPivotTarget.SetRotation(PivotTarget.GetRotation());
	SmoothedPivotTarget.SetScale3D(FVector{1.0f, 1.0f, 1.0f});

	PivotLocation = SmoothedPivotTarget.GetLocation() +
			SmoothedPivotTarget.GetRotation().GetForwardVector() * GetCameraBehaviorParam(FName("PivotOffset_X")) +
			SmoothedPivotTarget.GetRotation().GetRightVector() * GetCameraBehaviorParam(FName("PivotOffset_Y")) +
			SmoothedPivotTarget.GetRotation().GetUpVector() * GetCameraBehaviorParam(FName("PivotOffset_Z"));

	TargetCameraLocation = PivotLocation +
			TargetCameraRotation.Quaternion().GetForwardVector() * GetCameraBehaviorParam(FName("CameraOffset_X")) +
			TargetCameraRotation.Quaternion().GetRightVector() * GetCameraBehaviorParam(FName("CameraOffset_Y")) +
			TargetCameraRotation.Quaternion().GetUpVector() * GetCameraBehaviorParam(FName("CameraOffset_Z"));

	// FHitResult HitResult;
	// UKismetSystemLibrary::SphereTraceSingle(this, MainSpaceShip->GetActorLocation(), TargetCameraLocation, 10.0f,
	//		UEngineTypes::ConvertToTraceType(ECollisionChannel::ECC_Visibility), false, TArray<AActor*>(),
	//		EDrawDebugTrace::Type::None, HitResult, true);
	// if(HitResult.bBlockingHit && !HitResult.bStartPenetrating)
	// {
	//	TargetCameraLocation += HitResult.Location - HitResult.TraceEnd;
	// }
	
	ViewInfo.Location = TargetCameraLocation;
	ViewInfo.Rotation = TargetCameraRotation;
	ViewInfo.FOV = MainCharacter->ITCameraFOV;
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

FVector ARTFCameraManager::CalculateAxisIndependentLag(const FVector& CurrentLocation, const FVector& TargetLocation, const FRotator& CameraRotation, const FVector& LagSpeeds, float DeltaTime)
{
	const FQuat CameraQuatYaw = FRotator{0.0f, CameraRotation.Yaw, 0.0f}.Quaternion();
	const FVector CurrentLocationUnRotate = UKismetMathLibrary::Quat_UnrotateVector(CameraQuatYaw, CurrentLocation);
	const FVector TargetLocationUnRotate = UKismetMathLibrary::Quat_UnrotateVector(CameraQuatYaw, TargetLocation);
	return UKismetMathLibrary::Quat_RotateVector(CameraQuatYaw, FVector{
			UKismetMathLibrary::FInterpTo(CurrentLocationUnRotate.X, TargetLocationUnRotate.X, DeltaTime, LagSpeeds.X),
			UKismetMathLibrary::FInterpTo(CurrentLocationUnRotate.Y, TargetLocationUnRotate.Y, DeltaTime, LagSpeeds.Y),
			UKismetMathLibrary::FInterpTo(CurrentLocationUnRotate.Z, TargetLocationUnRotate.Z, DeltaTime, LagSpeeds.Z),
	});	
}

bool ARTFCameraManager::CanChangeCameraViewState(ECameraViewState NewState) const
{
	return CameraViewState != NewState && CameraViewState != ECameraViewState::ECVS_EmptyView;
}

