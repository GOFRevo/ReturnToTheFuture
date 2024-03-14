// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BaseSpaceShip.generated.h"

UCLASS()
class RETURNTOTHEFUTURE_API ABaseSpaceShip : public APawn
{
	GENERATED_BODY()
protected:
	// UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SpaceShip Properties", Meta = (AllowPrivateAccess = "true"))
	// class USkeletalMeshComponent* Mesh;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SpaceShip Properties", Meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement Properties", Meta = (AllowPrivateAccess = "true"))
	float Quality;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement Properties", Meta = (AllowPrivateAccess = "true"))
	float MaxForwardSpeed;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement Info", Meta = (AllowPrivateAccess = "true"))
	FVector SpaceShipVelocity;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement Info", Meta = (AllowPrivateAccess = "true"))
	FRotator SpaceShipRotationVelocity;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement Info", Meta = (AllowPrivateAccess = "true"))
	bool bForward;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement Info", Meta = (AllowPrivateAccess = "true"))
	bool bForwardTimeDecrease;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement Info", Meta = (AllowPrivateAccess = "true"))
	float ForwardTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement Properties", Meta = (AllowPrivateAccess = "true"))
	float MaxForwardTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement Properties", Meta = (AllowPrivateAccess = "true"))
	UCurveFloat* ForwardForceCurve;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement Info", Meta = (AllowPrivateAccess = "true"))
	bool bBack;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement Info", Meta = (AllowPrivateAccess = "true"))
	float BackTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement Properties", Meta = (AllowPrivateAccess = "true"))
	float MaxBackTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement Properties", Meta = (AllowPrivateAccess = "true"))
	UCurveFloat* BackForceCurve;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement Info|Right", Meta = (AllowPrivateAccess = "true"))
	float SpaceShipCurrentRollScale;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement Info|Right", Meta = (AllowPrivateAccess = "true"))
	float SpaceShipRollSpeed;	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement Info|Right", Meta = (AllowPrivateAccess = "true"))
	float SpaceShipBiasSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement Properties|Right", Meta = (AllowPrivateAccess = "true"))
	float SpaceShipMaxRollAngle;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement Properties|Right", Meta = (AllowPrivateAccess = "true"))
	float SpaceShipMaxRollTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement Properties|Right", Meta = (AllowPrivateAccess = "true"))
	float SpaceShipRightSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement Properties|Right", Meta = (AllowPrivateAccess = "true"))
	float SpaceShipRightBackScale;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement Properties|Right", Meta = (AllowPrivateAccess = "true"))
	float SpaceShipBiasDistance;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement Properties|Right", Meta = (AllowPrivateAccess = "true"))
	float SpaceShipRollBackSpeedScale;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement Properties|Right", Meta = (AllowPrivateAccess = "true"))
	float SpaceShipRollBackSpeedAngleBias;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement Properties|Right", Meta = (AllowPrivateAccess = "true"))
	float SpaceShipAcceRollBackSpeedScale;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement Info|Up", Meta = (AllowPrivateAccess = "true"))
	float SpaceShipCurrentPitchScale;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement Info|Up", Meta = (AllowPrivateAccess = "true"))
	float SpaceShipPitchSpeed;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement Info|Up", Meta = (AllowPrivateAccess = "true"))
	float SpaceShipPitchScaleCache;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement Info|Up", Meta = (AllowPrivateAccess = "true"))
	bool bSpaceShipPitchNeedRandom;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement Properties|Up", Meta = (AllowPrivateAccess = "true"))
	float SpaceShipMaxPitchAngle;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement Properties|Up", Meta = (AllowPrivateAccess = "true"))
	float SpaceShipMaxPitchTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement Properties|Up", Meta = (AllowPrivateAccess = "true"))
	float SpaceShipRightSpeedBias;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement Properties|Up", Meta = (AllowPrivateAccess = "true"))
	float SpaceShipUpSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement Properties|Up", Meta = (AllowPrivateAccess = "true"))
	float SpaceShipAccePitchBackSpeedScale;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement Properties|Up", Meta = (AllowPrivateAccess = "true"))
	float SpaceShipPitchBackSpeedScale;;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement Properties|Up", Meta = (AllowPrivateAccess = "true"))
	float SpaceShipPitchBackUpSpeedScale;;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement Properties|Up", Meta = (AllowPrivateAccess = "true"))
	float SpaceShipInverseUpSpeedScale;;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement Properties|Up", Meta = (AllowPrivateAccess = "true"))
	float SpaceShipInverseRightSpeedScale;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement Properties|Up", Meta = (AllowPrivateAccess = "true"))
	float SpaceShipPitchBackInterpSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement Properties|Up", Meta = (AllowPrivateAccess = "true"))
	float SpaceShipPitchInterpSpeed;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement Info|Up", Meta = (AllowPrivateAccess = "true"))
	float SpaceShipPitchRandomScale;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement Info|Up", Meta = (AllowPrivateAccess = "true"))
	float SpaceShipPitchRandomDirection;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement Info|Up", Meta = (AllowPrivateAccess = "true"))
	float SpaceShipPitchRandomAngle;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement Properties|Up", Meta = (AllowPrivateAccess = "true"))
	float SpaceShipPitchRandomOccurAngle;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement Properties|Up", Meta = (AllowPrivateAccess = "true"))
	float SpaceShipPitchRandomInterpSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement Properties|Up", Meta = (AllowPrivateAccess = "true"))
	float SpaceShipPitchRandomMinScale;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement Properties|Up", Meta = (AllowPrivateAccess = "true"))
	float SpaceShipPitchRandomMaxScale;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement Properties|Up", Meta = (AllowPrivateAccess = "true"))
	float SpaceShipPitchRandomMinAngle;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement Properties|Up", Meta = (AllowPrivateAccess = "true"))
	float SpaceShipPitchRandomMaxAngle;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement Properties|Forward", Meta = (AllowPrivateAccess = "true"))
	float SpaceShipAcceRightSpeedBias;
public:
	// Sets default values for this pawn's properties
	ABaseSpaceShip();
private:
	void UpdateMove(float DeltaTime);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	virtual void MoveForward(float DeltaTime);
	virtual void MoveBack(float DeltaTime);
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void BeginMoveForward();
	virtual void EndMoveForward();
	virtual void BeginMoveBack();
	virtual void EndMoveBack();
	virtual void MoveHorizon(float Scale);
	virtual void MoveVertical(float Scale);
	virtual void UpdateRightMove(float DeltaTime, FVector& TempVelocity, FRotator& NextRotation);
	virtual void UpdateUpMove(float DeltaTime, FVector& TempVelocity, FRotator& NextRotation);
	virtual void UpdateForwardMove(float DeltaTime, FVector& TempVelocity, FRotator& NextRotation);

	float MapRotationAngle(float Angle) const;
	float UnMapRotationAngle(float Angle) const;
	float RollAngleScale() const;
	float RollAngle() const;

	bool IsForwardAccelerating() const;
};
