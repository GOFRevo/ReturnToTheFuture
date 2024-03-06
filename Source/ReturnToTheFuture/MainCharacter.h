// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "MainCharacter.generated.h"

/**
 * 
 */
class AMainSpaceShip;
UCLASS()
class RETURNTOTHEFUTURE_API AMainCharacter : public ABaseCharacter
{
	GENERATED_BODY()

public:
	AMainCharacter();
	virtual void CalcCamera(float DeltaTime, FMinimalViewInfo& OutResult) override;
	void BeginMoveSpaceShipForward(AMainSpaceShip* SpaceShip);
	void EndMoveSpaceShipForward(AMainSpaceShip* SpaceShip);
	void BeginMoveSpaceShipBack(AMainSpaceShip* SpaceShip);
	void EndMoveSpaceShipBack(AMainSpaceShip* SpaceShip);
	
};
