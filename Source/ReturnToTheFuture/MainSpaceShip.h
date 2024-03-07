// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseSpaceShip.h"
#include "MainSpaceShip.generated.h"

/**
 * 
 */
UCLASS()
class RETURNTOTHEFUTURE_API AMainSpaceShip : public ABaseSpaceShip
{
	GENERATED_BODY()
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SpaceShip Info", Meta = (AllowPrivateAccess = "true"))
	class AMainCharacter* MainCharacter;
public:
	AMainSpaceShip();

	virtual void Tick(float DeltaSeconds) override;
	
	UFUNCTION(BlueprintCallable)
	AMainCharacter* GetMainCharacter() const;
	
	virtual void CalcCamera(float DeltaTime, FMinimalViewInfo& OutResult) override;
	void InitMainSpaceShipInfo();
};
