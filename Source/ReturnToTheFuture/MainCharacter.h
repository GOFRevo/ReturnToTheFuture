// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "MainCharacterEnums.h"
#include "MainCharacter.generated.h"

/**
 * 
 */
class AMainSpaceShip;
UCLASS()
class RETURNTOTHEFUTURE_API AMainCharacter : public ABaseCharacter
{
	GENERATED_BODY()
protected:
	ECharacterMainState CharacterMainState;

public:
	float ITCameraFOV;
	float IFCameraFOV;
	float OTCameraFOV;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Camera System", Meta = (AllowPrivateAccess = "true"))
	USceneComponent* IFCameraPivotTarget;
	
	AMainCharacter();
	
	virtual void BeginPlay() override;
	
	UFUNCTION(BlueprintCallable)
	ECharacterMainState GetCharacterMainState() const;
	UFUNCTION(BlueprintCallable)
	void SetCharacterMainState(ECharacterMainState NewState);
	
	virtual void CalcCamera(float DeltaTime, FMinimalViewInfo& OutResult) override;
	void BeginMoveSpaceShipForward(AMainSpaceShip* SpaceShip);
	void EndMoveSpaceShipForward(AMainSpaceShip* SpaceShip);
	void BeginMoveSpaceShipBack(AMainSpaceShip* SpaceShip);
	void EndMoveSpaceShipBack(AMainSpaceShip* SpaceShip);
	void MoveSpaceShipHorizon(AMainSpaceShip* SpaceShip, float Scale);
	void GetOffSpaceShip(AMainSpaceShip* SpaceShip);
	void GetOnSpaceShip(AMainSpaceShip* SpaceShip);
	void AttachToSpaceShip(AMainSpaceShip* SpaceShip);
	void DetachFromSpaceShip(AMainSpaceShip* SpaceShip);
	FTransform GetIFPivotTargetTransform() const;

	bool IsOnSpaceShip() const;
};
