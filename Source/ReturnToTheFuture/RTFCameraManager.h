// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CameraEnums.h"
#include "Camera/PlayerCameraManager.h"
#include "RTFCameraManager.generated.h"

/**
 * 
 */
UCLASS()
class RETURNTOTHEFUTURE_API ARTFCameraManager: public APlayerCameraManager
{
	GENERATED_BODY()
private:
	inline static ARTFCameraManager* InstancePointer = nullptr;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera Mesh", Meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* CameraBehavior;
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera Info", Meta = (AllowPrivateAccess = "true"))
	ECameraViewState CameraViewState;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera Info", Meta = (AllowPrivateAccess = "true"))
	class URTFCameraAnimInstance* RTFCameraAnimInstance;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera Info|Total", meta = (AllowPrivateAccess = "true"))
	FRotator TargetCameraRotation;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera Info|Total", meta = (AllowPrivateAccess = "true"))
	FVector TargetCameraLocation;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera Info|Total", meta = (AllowPrivateAccess = "true"))
	FVector PivotLocation;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera Info|Total", meta = (AllowPrivateAccess = "true"))
	FTransform SmoothedPivotTarget;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera Info|SpaceShip", meta = (AllowPrivateAccess = "true"))
	FRotator SpaceShipTargetCameraRotation;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera Info|SpaceShip", meta = (AllowPrivateAccess = "true"))
	FVector SpaceShipTargetCameraLocation;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera Info|SpaceShip", meta = (AllowPrivateAccess = "true"))
	FVector SpaceShipPivotLocation;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera Info|SpaceShip", meta = (AllowPrivateAccess = "true"))
	FTransform SmoothedSpaceShipPivotTarget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera Properties|SpaceShip", Meta = (AllowPrivateAccess = "true"))
	float RotationLagSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera Properties|SpaceShip", Meta = (AllowPrivateAccess = "true"))
	float PivotLagSpeedX;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera Properties|SpaceShip", Meta = (AllowPrivateAccess = "true"))
	float PivotLagSpeedY;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera Properties|SpaceShip", Meta = (AllowPrivateAccess = "true"))
	float PivotLagSpeedZ;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera Properties|SpaceShip", Meta = (AllowPrivateAccess = "true"))
	float PivotOffsetX;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera Properties|SpaceShip", Meta = (AllowPrivateAccess = "true"))
	float PivotOffsetY;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera Properties|SpaceShip", Meta = (AllowPrivateAccess = "true"))
	float PivotOffsetZ;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera Properties|SpaceShip", Meta = (AllowPrivateAccess = "true"))
	float CameraOffsetX;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera Properties|SpaceShip", Meta = (AllowPrivateAccess = "true"))
	float CameraOffsetY;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera Properties|SpaceShip", Meta = (AllowPrivateAccess = "true"))
	float CameraOffsetZ;
	
	ARTFCameraManager();

	void CustomCamera(float DeltaTime, FMinimalViewInfo& ViewInfo);
	static ARTFCameraManager* GetInstance();
	
	virtual void BeginPlay() override;
	
	UFUNCTION(Blueprintable)
	ECameraViewState GetCameraViewState() const;
	UFUNCTION(Blueprintable)
	void SetCameraViewState(ECameraViewState NewViewState);

	void SpaceShipCustomCamera(float DeltaTime, FMinimalViewInfo& ViewInfo);
	void SpaceShipCameraCache(float DeltaTime);
	void ITCustomCamera(float DeltaTime, FMinimalViewInfo& ViewInfo);
	void IFCustomCamera(float DeltaTime, FMinimalViewInfo& ViewInfo);
	void OTCustomCamera(float DeltaTime, FMinimalViewInfo& ViewInfo);

	void ToSpaceShipView();
	void ToITView();
	void ToIFView();
	void ToOTView();

	float GetCameraBehaviorParam(const FName& CurveName) const;
	FVector CalculateAxisIndependentLag(const FVector& CurrentLocation, const FVector& TargetLocation, const FRotator& CameraRotation, const FVector& LagSpeeds, float DeltaTime);

	bool CanChangeCameraViewState(ECameraViewState NewState) const;
};
