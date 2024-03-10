// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "CameraEnums.h"
#include "RTFCameraAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class RETURNTOTHEFUTURE_API URTFCameraAnimInstance: public UAnimInstance
{
	GENERATED_BODY()
private:
	void UpdateEssentialInfo();
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "CameraAnimInstance Info", Meta = (AllowPrivateAccess = "true"))
	ECameraViewState CameraViewState;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CameraAnimInstance Info", Meta = (AllowPrivateAccess = "true"))
	bool bIFToITHasCompelete;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CameraAnimInstance Info", Meta = (AllowPrivateAccess = "true"))
	bool bITToIFHasCompelete;

	URTFCameraAnimInstance();

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	void UpdateSpaceShipInfo();
	void UpdateSpaceShipCachedInfo();
	void UpdateITInfo();
	void UpdateIFInfo();
	void UpdateOTInfo();

	void ClearITCompeleteFlag();
	void ClearIFCompeleteFlag();
};
