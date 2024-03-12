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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement Info", Meta = (AllowPrivateAccess = "true"))
	float SpaceShipCurrentRollScale;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement Info", Meta = (AllowPrivateAccess = "true"))
	float SpaceShipRollSpeed;	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement Info", Meta = (AllowPrivateAccess = "true"))
	float SpaceShipBiasSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement Properties", Meta = (AllowPrivateAccess = "true"))
	float SpaceShipMaxRollAngle;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement Properties", Meta = (AllowPrivateAccess = "true"))
	float SpaceShipMaxRollTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement Properties", Meta = (AllowPrivateAccess = "true"))
	float SpaceShipRightSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement Properties", Meta = (AllowPrivateAccess = "true"))
	float SpaceShipRightBackScale;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement Properties", Meta = (AllowPrivateAccess = "true"))
	float SpaceShipBiasDistance;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement Properties", Meta = (AllowPrivateAccess = "true"))
	float SpaceShipRollBackSpeedScale;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement Properties", Meta = (AllowPrivateAccess = "true"))
	float SpaceShipAcceRollBackSpeedScale;
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

	float MapRotationAngle(float Angle) const;
	float UnMapRotationAngle(float Angle) const;
	float RollAngleScale() const;
	float RollAngle() const;

	bool IsForwardAccelerating() const;
};
