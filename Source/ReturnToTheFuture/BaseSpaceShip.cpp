// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseSpaceShip.h"
#include "BaseCameraManager.h"

// Sets default values
ABaseSpaceShip::ABaseSpaceShip():
	Quality(10.0f),
	MaxForwardSpeed(500.0f),
	SpaceShipVelocity(0.0f),
	bForward(false),
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

void ABaseSpaceShip::MoveForward(float DeltaTime)
{
	const float CurrentForwardSpeed = SpaceShipVelocity.X;
	if(CurrentForwardSpeed > MaxForwardSpeed)
	{
		UE_LOG(LogTemp, Warning, TEXT("%f"), ForwardTime);
		return;
	}
	SpaceShipVelocity.X = CurrentForwardSpeed +
		ForwardForceCurve->GetFloatValue(ForwardTime) * DeltaTime / Quality;
}

void ABaseSpaceShip::MoveBack(float DeltaTime)
{
	const float CurrentForwardSpeed = SpaceShipVelocity.X;
	if(CurrentForwardSpeed < 0.0f) return;
	SpaceShipVelocity.X = CurrentForwardSpeed -
		BackForceCurve->GetFloatValue(BackTime) * DeltaTime / Quality;
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
		ForwardTime = FMath::Min(ForwardTime, MaxForwardTime);
	}else
	{
		ForwardTime -= DeltaTime;
		ForwardTime = FMath::Max(0.0f, ForwardTime);
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

// Called to bind functionality to input
void ABaseSpaceShip::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ABaseSpaceShip::CalcCamera(float DeltaTime, FMinimalViewInfo& OutResult)
{
	const APlayerController* PlayerController = CastChecked<APlayerController>(GetController());
	ABaseCameraManager* BaseCameraManager = CastChecked<ABaseCameraManager>(PlayerController->PlayerCameraManager);
	if(!BaseCameraManager->CustomCamera(DeltaTime, OutResult))
	{
		Super::CalcCamera(DeltaTime, OutResult);
	}
}

void ABaseSpaceShip::BeginMoveForward()
{
	bForward = true;
}

void ABaseSpaceShip::EndMoveForward()
{
	bForward = false;
	
}

void ABaseSpaceShip::BeginMoveBack()
{
	bBack = true;
}

void ABaseSpaceShip::EndMoveBack()
{
	bBack = false;
	
}