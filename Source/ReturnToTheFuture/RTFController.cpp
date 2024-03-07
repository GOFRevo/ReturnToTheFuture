// Fill out your copyright notice in the Description page of Project Settings.


#include "RTFController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "MainSpaceShip.h"
#include "MainCharacter.h"
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
	ControllerState(EControllerState::ECS_IT)
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
	if(CanChangeView(EControllerState::ECS_SpaceShip))
	{
		ToSpaceShipView();
	}
}

void ARTFController::OnTwoPressed()
{
	if(CanChangeView(EControllerState::ECS_IT))
	{
		ToITView();
	}
}

void ARTFController::OnThreePressed()
{
	if(CanChangeView(EControllerState::ECS_IF))
	{
		ToIFView();
	}
}

void ARTFController::ToSpaceShipView()
{
	SetControllerState(EControllerState::ECS_SpaceShip);
}

void ARTFController::ToITView()
{
	SetControllerState(EControllerState::ECS_IT);
}

void ARTFController::ToIFView()
{
	SetControllerState(EControllerState::ECS_IF);
}

void ARTFController::ToOTView()
{
	SetControllerState(EControllerState::ECS_OT);
}

void ARTFController::OnTurn(const FInputActionValue& InputActionValue)
{
	const float InputScale = InputActionValue.GetMagnitude();
	switch(ControllerState)
	{
	case EControllerState::ECS_SpaceShip:
		SpaceShipOnTurn(InputScale);
		break;
	case EControllerState::ECS_IT:
		ITOnTurn(InputScale);
		break;
	case EControllerState::ECS_IF:
		IFOnTurn(InputScale);
		break;
	case EControllerState::ECS_OT:
		OTOnTurn(InputScale);
		break;
	default:
		check(false);
	}
}

void ARTFController::OnLookUp(const FInputActionValue& InputActionValue)
{
	const float InputScale = InputActionValue.GetMagnitude();
	switch(ControllerState)
	{
	case EControllerState::ECS_SpaceShip:
		SpaceShipOnLookUp(InputScale);
		break;
	case EControllerState::ECS_IT:
		ITOnLookUp(InputScale);
		break;
	case EControllerState::ECS_IF:
		IFOnLookUp(InputScale);
		break;
	case EControllerState::ECS_OT:
		OTOnLookUp(InputScale);
		break;
	default:
		check(false);
	}
}

void ARTFController::OnEPressed()
{
	if(CanGetOffSpaceShip())
	{
		ToOTView();
		MainCharacter->GetOffSpaceShip(MainSpaceShip);
		return;
	}
	if(CanGetOnSpaceShip())
	{
		MainCharacter->GetOnSpaceShip(MainSpaceShip);
		ToITView();
		return;
	}
}

void ARTFController::SpaceShipOnTurn(const float InputScale)
{
	AddYawInput(InputScale * SpaceShipTurnRate);
}

void ARTFController::SpaceShipOnLookUp(const float InputScale)
{
	AddPitchInput(InputScale * SpaceShipLookUpRate);
}

void ARTFController::ITOnTurn(const float InputScale)
{
	AddYawInput(InputScale * ITTurnRate);
}

void ARTFController::ITOnLookUp(const float InputScale)
{
	AddPitchInput(InputScale * ITLookUpRate);
}

void ARTFController::IFOnTurn(const float InputScale)
{
	AddYawInput(InputScale * IFTurnRate);
}

void ARTFController::IFOnLookUp(const float InputScale)
{
	AddPitchInput(InputScale * IFLookUpRate);
}

void ARTFController::OTOnTurn(const float InputScale)
{
	AddYawInput(InputScale * OTTurnRate);
}

void ARTFController::OTOnLookUp(const float InputScale)
{
	AddPitchInput(InputScale * OTLookUpRate);
}

bool ARTFController::CanCharacterInputMove() const
{
	return !MainCharacter->IsOnSpaceShip();
}

bool ARTFController::CanSpaceShipInputMove() const
{
	return MainCharacter->IsOnSpaceShip();
}

bool ARTFController::CanChangeView(EControllerState NewState) const
{
	return MainCharacter->IsOnSpaceShip() && GetControllerState() != NewState;
}

bool ARTFController::CanGetOffSpaceShip() const
{
	return MainCharacter->IsOnSpaceShip();
}

bool ARTFController::CanGetOnSpaceShip() const
{
	return !MainCharacter->IsOnSpaceShip();
}
