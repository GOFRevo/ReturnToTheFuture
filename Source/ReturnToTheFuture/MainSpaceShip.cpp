// Fill out your copyright notice in the Description page of Project Settings.


#include "MainSpaceShip.h"
#include "MainCharacter.h"
#include "RTFCameraManager.h"

AMainSpaceShip::AMainSpaceShip():
	MainCharacter(nullptr)
{
}

void AMainSpaceShip::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}


AMainCharacter* AMainSpaceShip::GetMainCharacter() const
{
	if(MainCharacter != nullptr) return MainCharacter;
	return CastChecked<AMainCharacter>(CastChecked<UChildActorComponent>(GetRootComponent()->GetChildComponent(0))->GetChildActor());
}

void AMainSpaceShip::CalcCamera(float DeltaTime, FMinimalViewInfo& OutResult)
{
	ARTFCameraManager::GetInstance()->CustomCamera(DeltaTime, OutResult);
}

void AMainSpaceShip::InitMainSpaceShipInfo()
{
	MainCharacter = GetMainCharacter();
}

