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
	IA_MoveForwardPressed(nullptr),
	IA_MoveBackPressed(nullptr),
	IA_MoveForwardReleased(nullptr),
	IA_MoveBackReleased(nullptr),
	IA_SpaceShipView(nullptr),
	IA_ITView(nullptr),
	IA_IFView(nullptr),
	IA_Turn(nullptr),
	IA_LookUp(nullptr),
	SpaceShipLookUpRate(1.25f),
	SpaceShipTurnRate(1.25f),
	ITLookUpRate(1.25f),
	ITTurnRate(1.25f),
	IFLookUpRate(1.25f),
	IFTurnRate(1.25f),
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
		if(IA_MoveForwardPressed)
		{
			enhancedInputComponent->BindAction(IA_MoveForwardPressed, ETriggerEvent::Triggered, this, &ARTFController::OnBeginMoveForward);
		}
		
		if(IA_MoveForwardReleased)
		{
			enhancedInputComponent->BindAction(IA_MoveForwardReleased, ETriggerEvent::Triggered, this, &ARTFController::OnEndMoveForward);
		}

		if(IA_MoveBackPressed)
		{
			enhancedInputComponent->BindAction(IA_MoveBackPressed, ETriggerEvent::Triggered, this, &ARTFController::OnBeginMoveBack);
		}
		
		if(IA_MoveBackReleased)
		{
			enhancedInputComponent->BindAction(IA_MoveBackReleased, ETriggerEvent::Triggered, this, &ARTFController::OnEndMoveBack);
		}
		
		if(IA_SpaceShipView)
		{
			enhancedInputComponent->BindAction(IA_SpaceShipView, ETriggerEvent::Triggered, this, &ARTFController::ToSpaceShipView);
		}
		
		if(IA_ITView)
		{
			enhancedInputComponent->BindAction(IA_ITView, ETriggerEvent::Triggered, this, &ARTFController::ToITView);
		}
		
		if(IA_IFView)
		{
			enhancedInputComponent->BindAction(IA_IFView, ETriggerEvent::Triggered, this, &ARTFController::ToIFView);
		}

		if(IA_Turn)
		{
			enhancedInputComponent->BindAction(IA_Turn, ETriggerEvent::Triggered, this, &ARTFController::OnTurn);
		}
		
		if(IA_LookUp)
		{
			enhancedInputComponent->BindAction(IA_LookUp, ETriggerEvent::Triggered, this, &ARTFController::OnLookUp);
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

void ARTFController::OnBeginMoveForward(const FInputActionValue& InputActionValue)
{
	if(!IsCharacterOnSpaceShip()) return;
	MainCharacter->BeginMoveSpaceShipForward(MainSpaceShip);
}

void ARTFController::OnEndMoveForward(const FInputActionValue& InputActionValue)
{
	if(!IsCharacterOnSpaceShip()) return;
	MainCharacter->EndMoveSpaceShipForward(MainSpaceShip);
}

void ARTFController::OnBeginMoveBack(const FInputActionValue& InputActionValue)
{
	if(!IsCharacterOnSpaceShip()) return;
	MainCharacter->BeginMoveSpaceShipBack(MainSpaceShip);
}

void ARTFController::OnEndMoveBack(const FInputActionValue& InputActionValue)
{
	if(!IsCharacterOnSpaceShip()) return;
	MainCharacter->EndMoveSpaceShipBack(MainSpaceShip);
}

void ARTFController::ToSpaceShipView()
{
	if(!IsCharacterOnSpaceShip()) return;
	if(GetControllerState() == EControllerState::ECS_SpaceShip) return;
	SetControllerState(EControllerState::ECS_SpaceShip);
}

void ARTFController::ToITView()
{
	if(!IsCharacterOnSpaceShip()) return;
	if(GetControllerState() == EControllerState::ECS_IT) return;
	SetControllerState(EControllerState::ECS_IT);
}

void ARTFController::ToIFView()
{
	if(!IsCharacterOnSpaceShip()) return;
	if(GetControllerState() == EControllerState::ECS_IF) return;
	SetControllerState(EControllerState::ECS_IF);
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
		break;
	default:
		check(false);
	}
}

bool ARTFController::IsCharacterOnSpaceShip() const
{
	return GetControllerState() != EControllerState::ECS_OT;
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

