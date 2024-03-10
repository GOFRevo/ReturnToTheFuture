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
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera Properties", Meta = (AllowPrivateAccess = "true"))
	UCurveFloat* SpaceShipFOVCurve;
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SpaceShip Info", Meta = (AllowPrivateAccess = "true"))
	class AMainCharacter* MainCharacter;
public:
	float SpaceShipCameraFOV;
	float SpaceShipCameraMinFOV;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera Properties", Meta = (AllowPrivateAccess = "true"))
	float SpaceShipCameraFOVSpeed;
	
	AMainSpaceShip();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	
	UFUNCTION(BlueprintCallable)
	AMainCharacter* GetMainCharacter() const;
	
	virtual void CalcCamera(float DeltaTime, FMinimalViewInfo& OutResult) override;
	void InitMainSpaceShipInfo();
	void UpdateFOV(float DeltaTime);
};
