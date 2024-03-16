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
	SpaceShipRealVelocity(0.0f),
	bForward(false),
	bForwardTimeDecrease(true),
	ForwardTime(0.0f),
	MaxForwardTime(4.0f),
	ForwardForceCurve(nullptr),
	bBack(false),
	BackTime(0.0f),
	MaxBackTime(2.0f),
	BackForceCurve(nullptr),
	//Right
	SpaceShipCurrentRollScale(0.0f),
	SpaceShipRollScaleCache(0.0f),
	bSpaceShipRollNeedRandom(false),
	SpaceShipRollRightSpeedScaleCache(1.0f),
	SpaceShipRollRightSpeedScaleInterpSpeed(10.0f),
	SpaceShipMaxRollAngle(20.0f),
	SpaceShipMaxRollTime(0.5f),
	SpaceShipUpSpeedBias(50.0f),
	SpaceShipRollUpSpeedScale(2.0f),
	SpaceShipRightSpeed(300.0f),
	SpaceShipAcceRollBackSpeedScale(2.0f),
	SpaceShipRollBackSpeedScale(0.8f),
	SpaceShipRollBackRightSpeedScale(2.0f),
	SpaceShipRollBackUpSpeedScale(0.4f),
	SpaceShipRollInverseUpSpeedScale(0.8f),
	SpaceShipRollInverseRightSpeedScale(0.2f),
	SpaceShipRollBackInterpSpeed(10.0f),
	SpaceShipRollInterpSpeed(12.0f),
	SpaceShipRollRandomScale(0.0f),
	SpaceShipRollRandomDirection(0.0f),
	SpaceShipRollRandomAngle(0.0f),
	SpaceShipRollRandomOccurAngle(16.0f),
	SpaceShipRollRandomInterpSpeed(12.0f),
	SpaceShipRollRandomMinScale(1.0f),
	SpaceShipRollRandomMaxScale(1.4f),
	SpaceShipRollRandomMinAngle(4.0f),
	SpaceShipRollRandomMaxAngle(8.0f),
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
	//Forward
	SpaceShipAcceRightSpeedBiasCurve(nullptr),
	SpaceShipAcceUpSpeedBiasCurve(nullptr),
	SpaceShipDecceRightSpeedBiasCurve(nullptr),
	SpaceShipDecceUpSpeedBiasCurve(nullptr),
	SpaceShipForwardRightSpeedBias(0.0f),
	SpaceShipForwardUpSpeedBias(0.0f),
	SpaceShipForwardUpInterpSpeed(40.0f),
	SpaceShipForwardRightInterpSpeed(80.0f),
	SpaceShipForwardRightMaxSpeedBias(150.0f),
	SpaceShipForwardUpMaxSpeedBias(150.0f)
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
	SpaceShipRealVelocity = SpaceShipVelocity + TempVelocity;
	SetActorLocation(CurrentActorLocation + SpaceShipRealVelocity * DeltaTime);
	SetActorRotation(NextRotation);
}

void ABaseSpaceShip::UpdateRightMove(float DeltaTime, FVector& TempVelocity, FRotator& NextRotation)
{
	// Update Right Movement
	float InputRollDirection = SpaceShipCurrentRollScale;
	const FRotator CurrentActorRotation = NextRotation;

	const float RollCurrentAngle = MapRotationAngle(CurrentActorRotation.Roll);
	const float RollAngleScale = RollCurrentAngle / SpaceShipMaxRollAngle;
	const float RollAngleAbsScale = FMath::Abs(RollAngleScale);
	const float RollAngleInverseAbsScale = 1.0f - RollAngleAbsScale;
	const float RollDirection = FRTFUtility::GetDirection(RollCurrentAngle);
	
	FRotator TempRotationVelocity{0.0f};
	float RollScale = SpaceShipRollScaleCache;
	float UpSpeedScale = SpaceShipRollUpSpeedScale * RollAngleInverseAbsScale;
	float RightSpeedScale = SpaceShipRollRightSpeedScaleCache;
	if(FMath::IsNearlyZero(InputRollDirection, 0.01f))
	{
		if(FMath::IsNearlyZero(RollCurrentAngle, 0.1f))
		{
			if(bSpaceShipRollNeedRandom)
			{
				RollScale = UKismetMathLibrary::FInterpTo(RollScale, SpaceShipRollRandomScale,
					 DeltaTime, SpaceShipRollRandomInterpSpeed);
			}else
			{
				NextRotation.Roll = 0.0f;
				RollScale = 0.0f;
			}
			UpSpeedScale = 0.0f;
			RightSpeedScale = 0.0f;
		}else
		{
			if(bSpaceShipRollNeedRandom) RollScale = UKismetMathLibrary::FInterpTo(RollScale, SpaceShipRollRandomScale, DeltaTime, SpaceShipRollRandomInterpSpeed);
			else RollScale = UKismetMathLibrary::FInterpTo(RollScale, -RollAngleScale * SpaceShipRollBackSpeedScale, DeltaTime, SpaceShipRollBackInterpSpeed);
			RightSpeedScale = UKismetMathLibrary::FInterpTo(RightSpeedScale, SpaceShipRollBackRightSpeedScale, DeltaTime, SpaceShipRollRightSpeedScaleInterpSpeed);
			UpSpeedScale = -SpaceShipRollBackUpSpeedScale * RollAngleAbsScale;
		}
	}else
	{
		if(!FRTFUtility::IsSameMark(InputRollDirection, RollCurrentAngle))
		{
			InputRollDirection *= SpaceShipAcceRollBackSpeedScale;
			RightSpeedScale = UKismetMathLibrary::FInterpTo(RightSpeedScale, SpaceShipRollInverseRightSpeedScale, DeltaTime, SpaceShipRollRightSpeedScaleInterpSpeed);
			UpSpeedScale = -SpaceShipRollInverseUpSpeedScale * RollAngleInverseAbsScale;
		}
		RollScale = UKismetMathLibrary::FInterpTo(RollScale, InputRollDirection, DeltaTime, SpaceShipRollInterpSpeed);
	}
	TempVelocity.Z += SpaceShipUpSpeedBias * UpSpeedScale;
	
	TempVelocity.Y += SpaceShipRightSpeed * RollAngleScale * RightSpeedScale;
	
	TempRotationVelocity.Roll += SpaceShipRollSpeed * RollScale;
	
	NextRotation = CurrentActorRotation + (SpaceShipRotationVelocity + TempRotationVelocity) * DeltaTime;
	
	if(bSpaceShipRollNeedRandom && FRTFUtility::IsSameMark(SpaceShipRollRandomDirection, MapRotationAngle(NextRotation.Roll)) &&
			FMath::Abs(MapRotationAngle(NextRotation.Roll)) > SpaceShipRollRandomAngle)
	{
		bSpaceShipRollNeedRandom = false;
		NextRotation.Roll = UnMapRotationAngle(SpaceShipRollRandomAngle * SpaceShipRollRandomDirection);
	}
	
	if(FMath::Abs(MapRotationAngle(NextRotation.Roll)) > SpaceShipRollRandomOccurAngle)
	{
		bSpaceShipRollNeedRandom = true;
		SpaceShipRollRandomDirection = -RollDirection;
		SpaceShipRollRandomScale = FMath::RandRange(SpaceShipRollRandomMinScale, SpaceShipRollRandomMaxScale) * SpaceShipRollRandomDirection;
		SpaceShipRollRandomAngle = FMath::RandRange(SpaceShipRollRandomMinAngle, SpaceShipRollRandomMaxAngle);
	}
	
	if(FMath::Abs(MapRotationAngle(NextRotation.Roll)) > SpaceShipMaxRollAngle)
	{
		NextRotation.Roll = UnMapRotationAngle(SpaceShipMaxRollAngle * RollDirection);
	}
	
	SpaceShipRollScaleCache = RollScale;
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
		if(FMath::IsNearlyZero(PitchCurrentAngle, 0.1f))
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
			UpSpeedScale = SpaceShipPitchBackUpSpeedScale;
		}
	}else
	{
		if(!FRTFUtility::IsSameMark(InputPitchDirection, PitchCurrentAngle))
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

	const float RollAngle = MapRotationAngle(NextRotation.Roll);
	const float RollAngleScale = RollAngle / SpaceShipMaxRollAngle;
	
	const float PitchAngle = NextRotation.Pitch;
	const float PitchAngleScale = PitchAngle / SpaceShipMaxPitchAngle;
	
	float TempAddZ = 0.0f;
	float TempAddY = 0.0f;
	if(bForward)
	{
		if(!FMath::IsNearlyZero(PitchAngle, 0.1f))
		{
			TempAddZ = PitchAngleScale * SpaceShipAcceUpSpeedBiasCurve->GetFloatValue(ForwardTime);
			TempAddY = RollAngleScale * SpaceShipAcceRightSpeedBiasCurve->GetFloatValue(ForwardTime);
		}
		MoveForward(DeltaTime);
	}

	if(bBack)
	{
		if(!FMath::IsNearlyZero(PitchAngle, 0.1f))
		{
			TempAddZ = -PitchAngleScale * SpaceShipDecceUpSpeedBiasCurve->GetFloatValue(BackTime);
			TempAddY = -RollAngleScale * SpaceShipDecceRightSpeedBiasCurve->GetFloatValue(BackTime);
		}
		MoveBack(DeltaTime);
	}
	/*
	if(bForward || bBack)
	{
		float NextVelocityZ = TempVelocity.Z + TempAddZ;
		float NextVelocityY = TempVelocity.Y + TempAddY;
		if(FRTFUtility::IsSameMark(NextVelocityZ, TempVelocity.Z)) TempVelocity.Z = TempVelocityZ;
		else TempVelocity.Z = 0.0f;
	}
	*/
	SpaceShipForwardUpSpeedBias = UKismetMathLibrary::FInterpTo(SpaceShipForwardUpSpeedBias, TempAddZ, DeltaTime, SpaceShipForwardUpInterpSpeed);
	SpaceShipForwardRightSpeedBias = UKismetMathLibrary::FInterpTo(SpaceShipForwardRightSpeedBias, TempAddY, DeltaTime, SpaceShipForwardRightInterpSpeed);
	TempVelocity.Z += SpaceShipForwardUpSpeedBias;
	TempVelocity.Y += SpaceShipForwardRightSpeedBias;
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

FVector ABaseSpaceShip::GetSpaceShipVelocity() const
{
	return SpaceShipRealVelocity;
}

float ABaseSpaceShip::GetForwardTime() const
{
	return ForwardTime;
}

float ABaseSpaceShip::GetMaxForwardTime() const
{
	return MaxForwardTime;
}

float ABaseSpaceShip::GetForwardPercent() const
{
	return GetForwardTime() / GetMaxForwardTime();
}

float ABaseSpaceShip::GetRightVelocity() const
{
	return SpaceShipRealVelocity.Y;	
}

float ABaseSpaceShip::GetUpVelocity() const
{
	return SpaceShipRealVelocity.Z;	
}

float ABaseSpaceShip::GetRightVelocityPercent() const
{
	return GetRightVelocity() / GetRightMaxVelocity();
}

float ABaseSpaceShip::GetUpVelocityPercent() const
{
	return GetUpVelocity() / GetUpMaxVelocity();
}

float ABaseSpaceShip::GetRightMaxVelocity() const
{
	return SpaceShipRightSpeed + SpaceShipForwardRightMaxSpeedBias;
}

float ABaseSpaceShip::GetUpMaxVelocity() const
{
	return SpaceShipUpSpeed + SpaceShipForwardUpMaxSpeedBias;
}

bool ABaseSpaceShip::IsForwardAccelerating() const
{
	return bForward;
}
