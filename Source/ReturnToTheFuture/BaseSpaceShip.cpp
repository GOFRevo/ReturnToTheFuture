// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseSpaceShip.h"

#include "RTFUtility.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
ABaseSpaceShip::ABaseSpaceShip():
	Quality(10.0f),
	MaxForwardSpeed(500.0f),
	SpaceShipVelocity(0.0f),
	SpaceShipRotationVelocity(0.0f),
	bForward(false),
	bForwardTimeDecrease(true),
	ForwardTime(0.0f),
	MaxForwardTime(4.0f),
	ForwardForceCurve(nullptr),
	bBack(false),
	BackTime(0.0f),
	MaxBackTime(2.0f),
	BackForceCurve(nullptr),
	SpaceShipCurrentRollScale(0.0f),
	SpaceShipMaxRollAngle(20.0f),
	SpaceShipMaxRollTime(0.5f),
	SpaceShipRightSpeed(300.0f),
	SpaceShipRightBackScale(1.0f),
	SpaceShipBiasDistance(20.0f),
	SpaceShipRollBackSpeedScale(1.0f),
	SpaceShipRollBackSpeedAngleBias(0.1f),
	SpaceShipAcceRollBackSpeedScale(2.0f),
	//Up
	SpaceShipCurrentPitchScale(0.0f),
	SpaceShipPitchScaleCache(0.0f),
	bSpaceShipPitchNeedRandom(false),
	SpaceShipMaxPitchAngle(10.0f),
	SpaceShipMaxPitchTime(0.3f),
	SpaceShipRightSpeedBias(20.0f),
	SpaceShipUpSpeed(300.0f),
	SpaceShipAccePitchBackSpeedScale(2.0f),
	SpaceShipPitchBackSpeedScale(1.0f),
	SpaceShipPitchBackUpSpeedScale(0.8f),
	SpaceShipInverseUpSpeedScale(0.2f),
	SpaceShipInverseRightSpeedScale(0.8f),
	SpaceShipPitchBackInterpSpeed(10.0f),
	SpaceShipPitchInterpSpeed(12.0f),
	SpaceShipPitchRandomScale(0.0f),
	SpaceShipPitchRandomDirection(0.0f),
	SpaceShipPitchRandomAngle(0.0f),
	SpaceShipPitchRandomOccurAngle(8.0f),
	SpaceShipPitchRandomInterpSpeed(12.0f),
	SpaceShipPitchRandomMinScale(1.0f),
	SpaceShipPitchRandomMaxScale(1.4f),
	SpaceShipPitchRandomMinAngle(2.0f),
	SpaceShipPitchRandomMaxAngle(4.0f),
	SpaceShipAcceRightSpeedBias(40.0f)
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
	FVector TempVelocity{0.0f};
	FRotator NextRotation = GetActorRotation();
	UpdateRightMove(DeltaTime, TempVelocity, NextRotation);
	UpdateUpMove(DeltaTime, TempVelocity, NextRotation);
	UpdateForwardMove(DeltaTime, TempVelocity, NextRotation);

	const FVector CurrentActorLocation = GetActorLocation();
	SetActorLocation(CurrentActorLocation + (SpaceShipVelocity + TempVelocity) * DeltaTime);
	SetActorRotation(NextRotation);
}

void ABaseSpaceShip::UpdateRightMove(float DeltaTime, FVector& TempVelocity, FRotator& NextRotation)
{
	// Update Right Movement
	FRotator TempRotationVelocity;
	float InputRollDirection = SpaceShipCurrentRollScale;
	const FRotator CurrentActorRotation = NextRotation;
	const float CurrentRollAngle = MapRotationAngle(CurrentActorRotation.Roll);
	const float AngleScale = FMath::Abs(CurrentRollAngle) / SpaceShipMaxRollAngle;
	const float RollDirection = CurrentRollAngle < 0.0f? -1.0f: 1.0f;
	const float RollSpeedScale = FMath::Abs(AngleScale) + SpaceShipRollBackSpeedAngleBias;
	if(FMath::IsNearlyZero(InputRollDirection, 0.01f))
	{
		if(FMath::IsNearlyZero(CurrentRollAngle, 0.1f))
		{
			NextRotation.Roll = 0.0f;
		}else
		{
			TempVelocity.Z -= SpaceShipBiasSpeed * SpaceShipRollBackSpeedScale * AngleScale;
			TempVelocity.Y += SpaceShipRightSpeed * SpaceShipRightBackScale * SpaceShipRollBackSpeedScale * -RollDirection * AngleScale;
			TempRotationVelocity.Roll = SpaceShipRollSpeed * SpaceShipRollBackSpeedScale * -RollDirection * RollSpeedScale;
			NextRotation = CurrentActorRotation + (SpaceShipRotationVelocity + TempRotationVelocity) * DeltaTime;
		}
	}else
	{
		if(InputRollDirection * CurrentRollAngle < 0.0f)
		{
			InputRollDirection *= SpaceShipAcceRollBackSpeedScale;
			TempVelocity.Y += SpaceShipRightSpeed * InputRollDirection * 0.1f;
			TempVelocity.Z += SpaceShipBiasSpeed * 0.4f;
		}else
		{
			TempVelocity.Y += SpaceShipRightSpeed * InputRollDirection * AngleScale;
		}
		TempRotationVelocity.Roll = SpaceShipRollSpeed * InputRollDirection;
		NextRotation = CurrentActorRotation + (SpaceShipRotationVelocity + TempRotationVelocity) * DeltaTime;
		if(FMath::Abs(MapRotationAngle(NextRotation.Roll)) < SpaceShipMaxRollAngle)
		{
			TempVelocity.Z += SpaceShipBiasSpeed * InputRollDirection * RollDirection * AngleScale;
		}else
		{
			NextRotation.Roll = UnMapRotationAngle(NextRotation.Roll > 0.0f? SpaceShipMaxRollAngle: -SpaceShipMaxRollAngle);
		}
	}
	SpaceShipCurrentRollScale = 0.0f;
}

void ABaseSpaceShip::UpdateUpMove(float DeltaTime, FVector& TempVelocity, FRotator& NextRotation)
{
	float InputPitchDirection = SpaceShipCurrentPitchScale;
	const FRotator CurrentActorRotation = NextRotation;
	
	const float RollCurrentAngle = MapRotationAngle(CurrentActorRotation.Roll);
	const float RollAngleScale = RollCurrentAngle / SpaceShipMaxRollAngle;

	const float PitchCurrentAngle = CurrentActorRotation.Pitch;
	const float PitchAngleScale = PitchCurrentAngle / SpaceShipMaxPitchAngle;
	const float PitchDirection = FRTFUtility::GetDirection(PitchCurrentAngle);

	FRotator TempRotationVelocity{0.0f};
	float PitchScale = SpaceShipPitchScaleCache;
	float UpSpeedScale = 1.0f;
	float RightSpeedScale = 1.0f;
	if(FMath::IsNearlyZero(InputPitchDirection, 0.01f))
	{
		if(FMath::IsNearlyZero(PitchCurrentAngle, 0.2f))
		{
			if(bSpaceShipPitchNeedRandom)
			{
				PitchScale = UKismetMathLibrary::FInterpTo(PitchScale, SpaceShipPitchRandomScale,
					 DeltaTime, SpaceShipPitchRandomInterpSpeed);
			}else
			{
				NextRotation.Pitch = 0.0f;
				PitchScale = 0.0f;
			}
			UpSpeedScale = 0.0f;
			RightSpeedScale = 0.0f;
		}else
		{
			if(bSpaceShipPitchNeedRandom) PitchScale = UKismetMathLibrary::FInterpTo(PitchScale, SpaceShipPitchRandomScale, DeltaTime, SpaceShipPitchRandomInterpSpeed);
			else PitchScale = UKismetMathLibrary::FInterpTo(PitchScale, -PitchAngleScale * SpaceShipPitchBackSpeedScale, DeltaTime, SpaceShipPitchBackInterpSpeed);
			UpSpeedScale = SpaceShipPitchBackSpeedScale;
		}
	}else
	{
		if(InputPitchDirection * PitchCurrentAngle < 0.0f)
		{
			InputPitchDirection *= SpaceShipAccePitchBackSpeedScale;
			UpSpeedScale = SpaceShipInverseUpSpeedScale;
			RightSpeedScale = SpaceShipInverseRightSpeedScale;
		}
		PitchScale = UKismetMathLibrary::FInterpTo(PitchScale, InputPitchDirection, DeltaTime, SpaceShipPitchInterpSpeed);
	}
	
	// const float NextTempVelocityY = TempVelocity.Y + SpaceShipRightSpeedBias * PitchAngleScale * RollAngleScale * RightSpeedScale;
	// if(NextTempVelocityY * TempVelocity.Y < 0.0f) TempVelocity.Y = 0.0f;
	// else	TempVelocity.Y = NextTempVelocityY;
	TempVelocity.Y += SpaceShipRightSpeedBias * PitchAngleScale * RollAngleScale * RightSpeedScale;
	
	TempVelocity.Z += SpaceShipUpSpeed * PitchAngleScale * UpSpeedScale;
	
	TempRotationVelocity.Pitch += SpaceShipPitchSpeed * PitchScale;
	
	NextRotation = CurrentActorRotation + (SpaceShipRotationVelocity + TempRotationVelocity) * DeltaTime;
	
	if(bSpaceShipPitchNeedRandom && FRTFUtility::IsSameMark(SpaceShipPitchRandomDirection, NextRotation.Pitch) && FMath::Abs(NextRotation.Pitch) > SpaceShipPitchRandomAngle)
	{
		bSpaceShipPitchNeedRandom = false;
		NextRotation.Pitch = SpaceShipPitchRandomAngle * SpaceShipPitchRandomDirection;
	}
	
	if(FMath::Abs(NextRotation.Pitch) > SpaceShipPitchRandomOccurAngle)
	{
		bSpaceShipPitchNeedRandom = true;
		SpaceShipPitchRandomDirection = -PitchDirection;
		SpaceShipPitchRandomScale = FMath::RandRange(SpaceShipPitchRandomMinScale, SpaceShipPitchRandomMaxScale) * SpaceShipPitchRandomDirection;
		SpaceShipPitchRandomAngle = FMath::RandRange(SpaceShipPitchRandomMinAngle, SpaceShipPitchRandomMaxAngle);
	}
	
	if(FMath::Abs(NextRotation.Pitch) > SpaceShipMaxPitchAngle)
	{
		NextRotation.Pitch = SpaceShipMaxPitchAngle * PitchDirection;
	}
	
	SpaceShipPitchScaleCache = PitchScale;
	SpaceShipCurrentPitchScale = 0.0f;
}

void ABaseSpaceShip::UpdateForwardMove(float DeltaTime, FVector& TempVelocity, FRotator& NextRotation)
{
	// Update Forward Movement
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
	SpaceShipRollSpeed = SpaceShipMaxRollAngle / SpaceShipMaxRollTime;
	SpaceShipBiasSpeed = SpaceShipBiasDistance / SpaceShipMaxRollTime;
	SpaceShipPitchSpeed = SpaceShipMaxPitchAngle / SpaceShipMaxPitchTime;
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

void ABaseSpaceShip::MoveHorizon(float Scale)
{
	SpaceShipCurrentRollScale = Scale;
}

void ABaseSpaceShip::MoveVertical(float Scale)
{
	SpaceShipCurrentPitchScale = Scale;
}

float ABaseSpaceShip::MapRotationAngle(float Angle) const
{
	if(Angle > 180.0f) return Angle - 360.0f;
	return Angle;
}

float ABaseSpaceShip::UnMapRotationAngle(float Angle) const
{
	if(Angle < 0.0f) return 360.0f + Angle;
	return Angle;
}

float ABaseSpaceShip::RollAngleScale() const
{
	return MapRotationAngle(GetActorRotation().Roll) / SpaceShipMaxRollAngle;
}

float ABaseSpaceShip::RollAngle() const
{
	return MapRotationAngle(GetActorRotation().Roll);
}

bool ABaseSpaceShip::IsForwardAccelerating() const
{
	return bForward;
}
