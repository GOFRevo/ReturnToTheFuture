// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CameraEnums.h"
#include "CameraStruct.h"
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
	ECameraViewState LastCameraViewState;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera Info", Meta = (AllowPrivateAccess = "true"))
	class URTFCameraAnimInstance* RTFCameraAnimInstance;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera Info|Total", meta = (AllowPrivateAccess = "true"))
	FCameraMovementInfo TotalCameraMovementInfo;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera Info|SpaceShip", meta = (AllowPrivateAccess = "true"))
	FCameraMovementInfo SpaceShipCameraMovementInfo;
	
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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera Properties|SpaceShip", Meta = (AllowPrivateAccess = "true"))
	FRotator SpaceShipCameraAccelDefaultRotation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera Properties|SpaceShip", Meta = (AllowPrivateAccess = "true"))
	float SpaceShipCameraAccelRotationSpeed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera Info|SpaceShip", meta = (AllowPrivateAccess = "true"))
	bool bSpaceShipCameraTransformNeedReset;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera Properties|SpaceShip", Meta = (AllowPrivateAccess = "true"))
	FRotator DefaultSpaceShipCameraRotation;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera Info|IT", meta = (AllowPrivateAccess = "true"))
	bool bITCameraTransformNeedReset;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera Properties|IT", Meta = (AllowPrivateAccess = "true"))
	FRotator DefaultITCameraRotation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera Properties|IT", Meta = (AllowPrivateAccess = "true"))
	float ITCameraRotationBias;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera Info|IF", meta = (AllowPrivateAccess = "true"))
	bool bIFCameraTransformNeedReset;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera Properties|IF", Meta = (AllowPrivateAccess = "true"))
	FRotator DefaultIFCameraRotation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera Properties|IFToIT", Meta = (AllowPrivateAccess = "true"))
	float IFToITTransitionSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera Properties|ITToIF", Meta = (AllowPrivateAccess = "true"))
	float ITToIFTransitionSpeed;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera Info|IF", meta = (AllowPrivateAccess = "true"))
	FRotator IFControlRotationCache;
	
	ARTFCameraManager();

	void CustomCamera(float DeltaTime, FMinimalViewInfo& ViewInfo);
	static ARTFCameraManager* GetInstance();
	
	virtual void BeginPlay() override;
	
	UFUNCTION(Blueprintable)
	ECameraViewState GetCameraViewState() const;
	UFUNCTION(Blueprintable)
	void SetCameraViewState(ECameraViewState NewViewState);
	UFUNCTION(Blueprintable)
	ECameraViewState GetLastCameraViewState() const;
	UFUNCTION(Blueprintable)
	void SetLastCameraViewState(ECameraViewState NewViewState);

	void SpaceShipCustomCamera(float DeltaTime, FMinimalViewInfo& ViewInfo);
	void SpaceShipCameraCache(float DeltaTime);
	void ITCustomCamera(float DeltaTime, FMinimalViewInfo& ViewInfo);
	void IFCustomCamera(float DeltaTime, FMinimalViewInfo& ViewInfo);
	void OTCustomCamera(float DeltaTime, FMinimalViewInfo& ViewInfo);

	void ToSpaceShipView();
	void ToITView();
	void ToIFView();
	void ToOTView();
	void ResetCameraTransform(ECameraViewState NewState);

	float GetCameraBehaviorParam(const FName& CurveName) const;
	FVector CalculateAxisIndependentLag(const FVector& CurrentLocation, const FVector& TargetLocation, const FRotator& CameraRotation, const FVector& LagSpeeds, float DeltaTime);

	bool CanChangeCameraViewState(ECameraViewState NewState) const;
	bool CanResetCameraTransform(ECameraViewState NewState) const;
	bool CanInterpCameraRotation() const;
};
