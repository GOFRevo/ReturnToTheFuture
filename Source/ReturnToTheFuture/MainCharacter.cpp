// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharacter.h"
#include "RTFCameraManager.h"
#include "MainSpaceShip.h"

AMainCharacter::AMainCharacter()
{
	
}

void AMainCharacter::CalcCamera(float DeltaTime, FMinimalViewInfo& OutResult)
{
	ARTFCameraManager::GetInstance()->CustomCamera(DeltaTime, OutResult);
}

void AMainCharacter::BeginMoveSpaceShipForward(AMainSpaceShip* SpaceShip)
{
	SpaceShip->BeginMoveForward();
}

void AMainCharacter::EndMoveSpaceShipForward(AMainSpaceShip* SpaceShip)
{
	SpaceShip->EndMoveForward();
}

void AMainCharacter::BeginMoveSpaceShipBack(AMainSpaceShip* SpaceShip)
{
	SpaceShip->BeginMoveBack();
}

void AMainCharacter::EndMoveSpaceShipBack(AMainSpaceShip* SpaceShip)
{
	SpaceShip->EndMoveBack();
}
