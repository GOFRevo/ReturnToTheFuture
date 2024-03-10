// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseSpaceShip.h"
#include "RTFUtility.h"

// Sets default values
ABaseSpaceShip::ABaseSpaceShip():
	Quality(10.0f),
	MaxForwardSpeed(500.0f),
	SpaceShipVelocity(0.0f),
	bForward(false),
	bForwardTimeDecrease(true),
	ForwardTime(0.0f),
	MaxForwardTime(4.0f),
	ForwardForceCurve(nullptr),
	bBack(false),
	BackTime(0.0f),
	MaxBackTime(2.0f),
	BackForceCurve(nullptr)
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SpaceShip Mesh"));
	// SetRootComponent(Mesh);
	
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SpaceShip Mesh"));
	SetRootComponent(Mesh);
}

void ABaseSpaceShip::UpdateMove(float DeltaTime)
{
	if(bBack)
	{
		bForward = false;
		BackTime += DeltaTime;
		BackTime = FMath::Min(BackTime, MaxBackTime);
	}else
	{
		BackTime -= DeltaTime;
		BackTime = FMath::Max(0.0f, BackTime);
	}
	
	if(bForward)
	{
		ForwardTime += DeltaTime;
		if(ForwardTime > MaxForwardTime)
		{
			ForwardTime = MaxForwardTime;
			bForward = false;
		}
	}else
	{
		if(bForwardTimeDecrease)
		{
			ForwardTime -= DeltaTime;
			ForwardTime = FMath::Max(0.0f, ForwardTime);
		}
	}

	if(bForward)
	{
		MoveForward(DeltaTime);
	}

	if(bBack)
	{
		MoveBack(DeltaTime);
	}

	const FVector CurrentActorLocation = GetActorLocation();
	SetActorLocation(CurrentActorLocation + SpaceShipVelocity * DeltaTime);
}


void ABaseSpaceShip::MoveForward(float DeltaTime)
{
	const float CurrentForwardSpeed = SpaceShipVelocity.X;
	if(CurrentForwardSpeed > MaxForwardSpeed) return;
	SpaceShipVelocity.X = CurrentForwardSpeed +
		ForwardForceCurve->GetFloatValue(ForwardTime) * DeltaTime / Quality;
}

void ABaseSpaceShip::MoveBack(float DeltaTime)
{
	const float CurrentForwardSpeed = SpaceShipVelocity.X;
	if(FMath::Abs(CurrentForwardSpeed) < 10e-6) return;
	SpaceShipVelocity.X = CurrentForwardSpeed -
		BackForceCurve->GetFloatValue(BackTime) * DeltaTime / Quality;
	SpaceShipVelocity.X = FMath::Max(0.0f, SpaceShipVelocity.X);
}

// Called when the game starts or when spawned
void ABaseSpaceShip::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseSpaceShip::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UpdateMove(DeltaTime);
}

// Called to bind functionality to input
void ABaseSpaceShip::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ABaseSpaceShip::BeginMoveForward()
{
	bForward = true;
	bForwardTimeDecrease = false;
}

void ABaseSpaceShip::EndMoveForward()
{
	bForward = false;
	bForwardTimeDecrease = true;
}

void ABaseSpaceShip::BeginMoveBack()
{
	bBack = true;
}

void ABaseSpaceShip::EndMoveBack()
{
	bBack = false;
	
}