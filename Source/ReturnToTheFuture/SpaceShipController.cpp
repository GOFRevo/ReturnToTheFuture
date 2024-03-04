// Fill out your copyright notice in the Description page of Project Settings.


#include "SpaceShipController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "SpaceShipCameraManager.h"
#include "MainSpaceShip.h"

ASpaceShipController::ASpaceShipController():
	SpaceShipCameraManager(nullptr),
	MainSpaceShip(nullptr),
	InputMappingContext(nullptr),
	IA_MoveForwardPressed(nullptr),
	IA_MoveBackPressed(nullptr),
	IA_MoveForwardReleased(nullptr),
	IA_MoveBackReleased(nullptr)
{
}

void ASpaceShipController::OnPossess(APawn* SpaceShip)
{
	Super::OnPossess(SpaceShip);
	if(SpaceShipCameraManager == nullptr)
	{
		SpaceShipCameraManager = CastChecked<ASpaceShipCameraManager>(PlayerCameraManager);
		SpaceShipCameraManager->OnPosses(SpaceShip);
	}
	if(MainSpaceShip == nullptr)
	{
		MainSpaceShip = CastChecked<AMainSpaceShip>(SpaceShip);
	}
}

void ASpaceShipController::SetupInputComponent()
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
			enhancedInputComponent->BindAction(IA_MoveForwardPressed, ETriggerEvent::Triggered, this, &ASpaceShipController::OnMoveForwardBegin);
		}
		
		if(IA_MoveForwardReleased)
		{
			enhancedInputComponent->BindAction(IA_MoveForwardReleased, ETriggerEvent::Triggered, this, &ASpaceShipController::OnMoveForwardEnd);
		}

		if(IA_MoveBackPressed)
		{
			enhancedInputComponent->BindAction(IA_MoveBackPressed, ETriggerEvent::Triggered, this, &ASpaceShipController::OnMoveBackBegin);
		}
		
		if(IA_MoveBackReleased)
		{
			enhancedInputComponent->BindAction(IA_MoveBackReleased, ETriggerEvent::Triggered, this, &ASpaceShipController::OnMoveBackEnd);
		}
	}
}

void ASpaceShipController::OnMoveForwardBegin()
{
	MainSpaceShip->BeginMoveForward();
}

void ASpaceShipController::OnMoveForwardEnd()
{
	MainSpaceShip->EndMoveForward();
}

void ASpaceShipController::OnMoveBackBegin()
{
	MainSpaceShip->BeginMoveBack();
}

void ASpaceShipController::OnMoveBackEnd()
{
	MainSpaceShip->EndMoveBack();
}
