// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "SpaceShipCameraAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class RETURNTOTHEFUTURE_API USpaceShipCameraAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AnimInstance Info", Meta = (AllowPrivateAccess = "true"))
	class ASpaceShipController* SpaceShipController;
	
public:
	USpaceShipCameraAnimInstance();
};
