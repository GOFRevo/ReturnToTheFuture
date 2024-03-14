// Fill out your copyright notice in the Description page of Project Settings.
#include "RTFController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "MainSpaceShip.h"
#include "MainCharacter.h"
#include "RTFCameraManager.h"
#include "RTFUtility.h"
#include "Components/CapsuleComponent.h"

ARTFController::ARTFController():
	MainSpaceShip(nullptr),
	MainCharacter(nullptr),
	InputMappingContext(nullptr),
	IA_WAxis(nullptr),
	IA_DAxis(nullptr),
	IA_ShiftPressed(nullptr),
	IA_ShiftReleased(nullptr),
	IA_SpacePressed(nullptr),
	IA_SpaceReleased(nullptr),
	IA_OnePressed(nullptr),
	IA_TwoPressed(nullptr),
	IA_ThreePressed(nullptr),
	IA_Turn(nullptr),
	IA_LookUp(nullptr),
	IA_EPressed(nullptr),
	SpaceShipLookUpRate(1.25f),
	SpaceShipTurnRate(1.25f),
	ITLookUpRate(1.25f),
	ITTurnRate(1.25f),
	IFLookUpRate(1.25f),
	IFTurnRate(1.25f),
	OTLookUpRate(1.25f),
	OTTurnRate(1.25f),
	bAllowTurnLookup(true),
	SpaceShipMaxAngle(0.0f),
	SpaceShipDeadZoneAngle(0.0f),
	SpaceShipDeadZoneRate(0.0f),
	SpaceShipDeadZoneSpeed(0.0f),
	ITMaxAngle(0.0f),
	ITDeadZoneAngle(0.0f),
	ITDeadZoneRate(0.0f),
	ITDeadZoneSpeed(0.0f),
	IFMaxAngle(0.0f),
	IFDeadZoneAngle(0.0f),
	IFDeadZoneRate(0.0f),
	IFDeadZoneSpeed(0.0f),
	ControllerState(EControllerState::ECS_IT),
	ControlViewState(EControlViewState::ECVS_UserView)
{
	InstancePointer = this;
}

ARTFController* ARTFController::GetInstance()
{
	check(InstancePointer != nullptr)
	return InstancePointer;
}

void ARTFController::SetupInputComponent()
{
	Super::SetupInputComponent();
	if(UEnhancedInputLocalPlayerSubsystem* subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		subsystem->AddMappingContext(InputMappingContext, 100);
	}
	
	if(UEnhancedInputComponent* enhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent))
	{
		if(IA_WAxis)
		{
			enhancedInputComponent->BindAction(IA_WAxis, ETriggerEvent::Triggered, this, &ARTFController::OnWAxis);
		}
		
		if(IA_DAxis)
		{
			enhancedInputComponent->BindAction(IA_DAxis, ETriggerEvent::Triggered, this, &ARTFController::OnDAxis);
		}
		
		if(IA_ShiftPressed)
		{
			enhancedInputComponent->BindAction(IA_ShiftPressed, ETriggerEvent::Triggered, this, &ARTFController::OnShiftPressed);
		}
		
		if(IA_ShiftReleased)
		{
			enhancedInputComponent->BindAction(IA_ShiftReleased, ETriggerEvent::Triggered, this, &ARTFController::OnShiftReleased);
		}

		if(IA_SpacePressed)
		{
			enhancedInputComponent->BindAction(IA_SpacePressed, ETriggerEvent::Triggered, this, &ARTFController::OnSpacePressed);
		}
		
		if(IA_SpaceReleased)
		{
			enhancedInputComponent->BindAction(IA_SpaceReleased, ETriggerEvent::Triggered, this, &ARTFController::OnSpaceReleased);
		}
		
		if(IA_OnePressed)
		{
			enhancedInputComponent->BindAction(IA_OnePressed, ETriggerEvent::Triggered, this, &ARTFController::OnOnePressed);
		}
		
		if(IA_TwoPressed)
		{
			enhancedInputComponent->BindAction(IA_TwoPressed, ETriggerEvent::Triggered, this, &ARTFController::OnTwoPressed);
		}
		
		if(IA_ThreePressed)
		{
			enhancedInputComponent->BindAction(IA_ThreePressed, ETriggerEvent::Triggered, this, &ARTFController::OnThreePressed);
		}

		if(IA_Turn)
		{
			enhancedInputComponent->BindAction(IA_Turn, ETriggerEvent::Triggered, this, &ARTFController::OnTurn);
		}
		
		if(IA_LookUp)
		{
			enhancedInputComponent->BindAction(IA_LookUp, ETriggerEvent::Triggered, this, &ARTFController::OnLookUp);
		}

		if(IA_EPressed)
		{
			enhancedInputComponent->BindAction(IA_EPressed, ETriggerEvent::Triggered, this, &ARTFController::OnEPressed);
		}
	}
}

void ARTFController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	switch(GetControlViewState())
	{
	case EControlViewState::ECVS_UserView:
		EscapeDeadZone();
		break;
	case EControlViewState::ECVS_ShowView:
		break;
	default:
		check(0);
	}
}


void ARTFController::InitControllerInfo(APawn* SpaceShip)
{
	if(MainSpaceShip != nullptr) return;
	MainSpaceShip = CastChecked<AMainSpaceShip>(SpaceShip);
	MainSpaceShip->InitMainSpaceShipInfo();
	MainCharacter = MainSpaceShip->GetMainCharacter();
	MainCharacter->GetCapsuleComponent()->SetCollisionProfileName(TEXT("NoCollision"), true);
}

EControllerState ARTFController::GetControllerState() const
{
	return ControllerState;
}

void ARTFController::SetControllerState(EControllerState NewState)
{
	ControllerState = NewState;
}

EControlViewState ARTFController::GetControlViewState() const
{
	return ControlViewState;
}

void ARTFController::SetControlViewState(EControlViewState NewState)
{
	ControlViewState = NewState;
}

AMainCharacter* ARTFController::GetMainCharacter() const
{
	return MainCharacter;
}

AMainSpaceShip* ARTFController::GetMainSpaceShip() const
{
	return MainSpaceShip;
}

void ARTFController::OnWAxis(const FInputActionValue& InputActionValue)
{
	if(CanSpaceShipInputMove())
	{
		MainCharacter->MoveSpaceShipVertical(MainSpaceShip, InputActionValue.GetMagnitude());
		return;
	}
	if(CanCharacterInputMove())
	{
		MainCharacter->PlayMovementInput(true, InputActionValue.GetMagnitude());
		return;
	}
}

void ARTFController::OnDAxis(const FInputActionValue& InputActionValue)
{
	if(CanSpaceShipInputMove())
	{
		MainCharacter->MoveSpaceShipHorizon(MainSpaceShip, InputActionValue.GetMagnitude());
		return;
	}
	if(CanCharacterInputMove())
	{
		MainCharacter->PlayMovementInput(false, InputActionValue.GetMagnitude());
		return;
	}
}

void ARTFController::OnShiftPressed()
{
	if(CanSpaceShipInputMove())
	{
		MainCharacter->BeginMoveSpaceShipForward(MainSpaceShip);
	}
}

void ARTFController::OnShiftReleased()
{
	if(CanSpaceShipInputMove())
	{
		MainCharacter->EndMoveSpaceShipForward(MainSpaceShip);
	}
}

void ARTFController::OnSpacePressed()
{
	if(CanSpaceShipInputMove())
	{
		MainCharacter->BeginMoveSpaceShipBack(MainSpaceShip);
		return;
	}
	if(CanCharacterInputMove())
	{
		return;
	}
}

void ARTFController::OnSpaceReleased()
{
	if(CanSpaceShipInputMove())
	{
		MainCharacter->EndMoveSpaceShipBack(MainSpaceShip);
	}
}

void ARTFController::OnOnePressed()
{
	if(CanChangeControlState(EControllerState::ECS_SpaceShip))
	{
		ToSpaceShipControl();
	}
}

void ARTFController::OnTwoPressed()
{
	if(CanChangeControlState(EControllerState::ECS_IT))
	{
		ToITControl();
	}
}

void ARTFController::OnThreePressed()
{
	if(CanChangeControlState(EControllerState::ECS_IF))
	{
		ToIFControl();
	}
}

void ARTFController::ToSpaceShipControl()
{
	SetControllerState(EControllerState::ECS_SpaceShip);
	ARTFCameraManager* CameraManager = ARTFCameraManager::GetInstance();
	if(CameraManager->CanChangeCameraViewState(ECameraViewState::ECVS_SpaceShipView))
	{
		CameraManager->ToSpaceShipView();
	}
}

void ARTFController::ToITControl()
{
	SetControllerState(EControllerState::ECS_IT);
	ARTFCameraManager* CameraManager = ARTFCameraManager::GetInstance();
	if(CameraManager->CanChangeCameraViewState(ECameraViewState::ECVS_ITView))
	{
		CameraManager->ToITView();
	}
}

void ARTFController::ToIFControl()
{
	SetControllerState(EControllerState::ECS_IF);
	ARTFCameraManager* CameraManager = ARTFCameraManager::GetInstance();
	if(CameraManager->CanChangeCameraViewState(ECameraViewState::ECVS_IFView))
	{
		CameraManager->ToIFView();
	}
}

void ARTFController::ToOTControl()
{
	SetControllerState(EControllerState::ECS_OT);
	ARTFCameraManager* CameraManager = ARTFCameraManager::GetInstance();
	if(CameraManager->CanChangeCameraViewState(ECameraViewState::ECVS_OTView))
	{
		CameraManager->ToOTView();
	}
}

void ARTFController::OnTurn(const FInputActionValue& InputActionValue)
{
	const float InputScale = InputActionValue.GetMagnitude();
	const ARTFCameraManager* CameraManager = ARTFCameraManager::GetInstance();
	switch(CameraManager->GetCameraViewState())
	{
	case ECameraViewState::ECVS_SpaceShipView:
		ViewOnTurn(InputScale,  SpaceShipTurnRate, true, SpaceShipDeadZoneAngle, SpaceShipDeadZoneRate, SpaceShipMaxAngle);
		break;
	case ECameraViewState::ECVS_ITView:
		ViewOnTurn(InputScale,  ITTurnRate, true, ITDeadZoneAngle, ITDeadZoneRate, ITMaxAngle);
		break;
	case ECameraViewState::ECVS_IFView:
		ViewOnTurn(InputScale,  ITTurnRate, true, IFDeadZoneAngle, IFDeadZoneRate, IFMaxAngle);
		break;
	case ECameraViewState::ECVS_OTView:
		ViewOnTurn(InputScale,  OTTurnRate, false);
		break;
	default:
		check(false);
	}
}

void ARTFController::OnLookUp(const FInputActionValue& InputActionValue)
{
	const float InputScale = InputActionValue.GetMagnitude();
	const ARTFCameraManager* CameraManager = ARTFCameraManager::GetInstance();
	switch(CameraManager->GetCameraViewState())
	{
	case ECameraViewState::ECVS_SpaceShipView:
		ViewOnLookUp(InputScale, SpaceShipLookUpRate,true, SpaceShipDeadZoneAngle, SpaceShipDeadZoneRate, SpaceShipMaxAngle);
		break;
	case ECameraViewState::ECVS_ITView:
		ViewOnLookUp(InputScale, ITLookUpRate, true, ITDeadZoneAngle, ITDeadZoneRate, ITMaxAngle);
		break;
	case ECameraViewState::ECVS_IFView:
		ViewOnLookUp(InputScale, IFLookUpRate, true,IFDeadZoneAngle, IFDeadZoneRate, IFMaxAngle);
		break;
	case ECameraViewState::ECVS_OTView:
		ViewOnLookUp(InputScale, OTLookUpRate, false);
		break;
	default:
		check(false);
	}
}

void ARTFController::OnEPressed()
{
	if(CanGetOffSpaceShip())
	{
		ToOTControl();
		MainCharacter->GetOffSpaceShip(MainSpaceShip);
		return;
	}
	if(CanGetOnSpaceShip())
	{
		MainCharacter->GetOnSpaceShip(MainSpaceShip);
		ToITControl();
		return;
	}
}

void ARTFController::ViewOnTurn(const float InputScale, const float TurnRate, const bool bDeadZone, const float DeadZoneAngle, const float DeadZoneRate, const float MaxAngle)
{
	if(!CanTurnAndLook()) return;
	const FRotator CurRotation = GetControlRotation();
	const float Value = InputScale * TurnRate;
	if(!bDeadZone)
	{
		SetControlRotation(CurRotation + FRotator{0.0f, Value, 0.0f});
		return;
	}
	const float YawAngle = MapControlRotation(GetControlRotation().Yaw) + Value;
	const float PitchAngle = MapControlRotation(GetControlRotation().Pitch);
	const float CurValue = YawAngle * YawAngle + PitchAngle * PitchAngle;

	const float Max = MaxAngle * MaxAngle;
	const float Min = DeadZoneAngle * DeadZoneAngle;
	if(CurValue >= Max) return;
	if(CurValue <= Min)
	{
		SetControlRotation(CurRotation + FRotator{0.0f, Value, 0.0f});
	}else
	{
		SetControlRotation(CurRotation + FRotator{0.0f, InputScale * DeadZoneRate * FRTFUtility::Interp(Max, Min, CurValue), 0.0f});
	}
}

void ARTFController::ViewOnLookUp(const float InputScale, const float LookupRate, const bool bDeadZone, const float DeadZoneAngle, const float DeadZoneRate, const float MaxAngle)
{
	if(!CanTurnAndLook()) return;
	const FRotator CurRotation = GetControlRotation();
	const float Value = InputScale * LookupRate;
	if(!bDeadZone)
	{
		SetControlRotation(CurRotation - FRotator{Value, 0.0f, 0.0f});
		return;
	}
	const float YawAngle = MapControlRotation(GetControlRotation().Yaw);
	const float PitchAngle = MapControlRotation(GetControlRotation().Pitch) - Value;
	const float CurValue = YawAngle * YawAngle + PitchAngle * PitchAngle;

	const float Max = MaxAngle * MaxAngle;
	const float Min = DeadZoneAngle * DeadZoneAngle;
	if(CurValue >= Max) return;
	if(CurValue <= Min)
	{
		SetControlRotation(CurRotation - FRotator{Value, 0.0f, 0.0f});
	}else
	{
		SetControlRotation(CurRotation - FRotator{InputScale * DeadZoneRate * FRTFUtility::Interp(Max, Min, CurValue), 0.0f, 0.0f});
	}
}

void ARTFController::BlockTurnAndLook()
{
	bAllowTurnLookup = false;
}

void ARTFController::OpenTurnAndLook()
{
	bAllowTurnLookup = true;
}

void ARTFController::EscapeDeadZone()
{
	const ECameraViewState CameraViewState = ARTFCameraManager::GetInstance()->GetCameraViewState();
	switch(CameraViewState)
	{
	case ECameraViewState::ECVS_SpaceShipView:
		EscapeDeadZoneImpl(SpaceShipDeadZoneAngle, SpaceShipDeadZoneSpeed);
		break;
	case ECameraViewState::ECVS_ITView:
		EscapeDeadZoneImpl(ITDeadZoneAngle, ITDeadZoneSpeed);
		break;
	case ECameraViewState::ECVS_IFView:
		EscapeDeadZoneImpl(IFDeadZoneAngle, IFDeadZoneSpeed);
		break;
	case ECameraViewState::ECVS_OTView:
		break;
	case ECameraViewState::ECVS_EmptyView:
		break;
	default:
		check(0)
	}
	
}

void ARTFController::EscapeDeadZoneImpl(const float DeadZoneAngle, const float DeadZoneSpeed)
{
	FRotator CurRotation = GetControlRotation();
	const float YawAngle = MapControlRotation(CurRotation.Yaw);
	const float PitchAngle = MapControlRotation(CurRotation.Pitch);
	
	const float Length = YawAngle * YawAngle + PitchAngle * PitchAngle;
	if(DeadZoneAngle * DeadZoneAngle > Length) return;
	
	const float YawDir = YawAngle > 0.0f? -1.0f: 1.0f;
	const float AbsPitch = FMath::Abs(PitchAngle);
	if(AbsPitch < 1.0f)
	{
		SetControlRotation(CurRotation + FRotator{0.0f, DeadZoneSpeed * YawDir, 0.0f});
		return;
	}
	const float PitchDir = PitchAngle > 0.0f? -1.0f: 1.0f;
	const float AbsYaw = FMath::Abs(YawAngle);
	if(AbsYaw < 1.0f)
	{
		SetControlRotation(CurRotation + FRotator{DeadZoneSpeed * PitchDir, 0.0f, 0.0f});
		return;
	}
	const float Sin = FRTFUtility::CalcuSin(AbsPitch, AbsYaw);
	const float Cos = Sin * AbsPitch / AbsYaw;
	SetControlRotation(CurRotation + FRotator{DeadZoneSpeed * PitchDir * Cos, 0.0f, 0.0f});
	CurRotation = GetControlRotation();
	SetControlRotation(CurRotation + FRotator{0.0f, DeadZoneSpeed * YawDir * Sin, 0.0f});
}

float ARTFController::MapControlRotation(const float Angle) const
{
	if(Angle > 270.0f) return Angle - 360.0f;
	return Angle;
}

bool ARTFController::CanCharacterInputMove() const
{
	return !MainCharacter->IsOnSpaceShip();
}

bool ARTFController::CanSpaceShipInputMove() const
{
	return MainCharacter->IsOnSpaceShip();
}

bool ARTFController::CanChangeControlState(EControllerState NewState) const
{
	return MainCharacter->IsOnSpaceShip() && GetControllerState() != NewState
		&& GetControllerState() != EControllerState::ECS_Idle;
}

bool ARTFController::CanGetOffSpaceShip() const
{
	return MainCharacter->IsOnSpaceShip();
}

bool ARTFController::CanGetOnSpaceShip() const
{
	return !MainCharacter->IsOnSpaceShip();
}

bool ARTFController::CanCacheSpaceShipCamera() const
{
	return MainCharacter->IsOnSpaceShip();
}

bool ARTFController::CanTurnAndLook() const
{
	return bAllowTurnLookup;
}


