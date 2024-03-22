// Fill out your copyright notice in the Description page of Project Settings.


#include "MainSpaceShip.h"
#include "MainCharacter.h"
#include "RTFCameraManager.h"
#include "Kismet/KismetMathLibrary.h"

AMainSpaceShip::AMainSpaceShip():
	SpaceShipFOVCurve(nullptr),
	MainCharacter(nullptr),
	SpaceShipCameraFOV(0.0f),
	SpaceShipCameraMinFOV(0.0f),
	SpaceShipCameraFOVSpeed(1.0f)
{
}

void AMainSpaceShip::BeginPlay()
{
	Super::BeginPlay();
	
	UE_LOG(LogTemp, Warning, TEXT("%s"), *FPaths::ProjectModsDir());
	SpaceShipCameraMinFOV = SpaceShipFOVCurve->GetFloatValue(MaxForwardTime);
	SpaceShipCameraFOV = SpaceShipCameraMinFOV;
}

void AMainSpaceShip::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	UpdateFOV(DeltaSeconds);
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

void AMainSpaceShip::UpdateFOV(float DeltaTime)
{
	float FOVTarget = SpaceShipCameraMinFOV;
	if(bForward) FOVTarget = SpaceShipFOVCurve->GetFloatValue(ForwardTime);
	SpaceShipCameraFOV = UKismetMathLibrary::FInterpTo(SpaceShipCameraFOV, FOVTarget, DeltaTime, SpaceShipCameraFOVSpeed);
}


