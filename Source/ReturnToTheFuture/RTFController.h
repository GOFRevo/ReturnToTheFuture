// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ControllerEnums.h"
#include "RTFController.generated.h"

class UInputMappingContext;
class UInputAction;
/**
 * 
 */
UCLASS()
class RETURNTOTHEFUTURE_API ARTFController: public APlayerController
{
	GENERATED_BODY()
private:
	inline static ARTFController* InstancePointer = nullptr;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Controller Info", Meta = (AllowPrivateAccess = "true"))
	class AMainSpaceShip* MainSpaceShip;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Controller Info", Meta = (AllowPrivateAccess = "true"))
	class AMainCharacter* MainCharacter;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Input", Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputMappingContext> InputMappingContext;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Input|Action", Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> IA_WAxis;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Input|Action", Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> IA_DAxis;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Input|Action", Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> IA_ShiftPressed;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Input|Action", Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> IA_ShiftReleased;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Input|Action", Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> IA_SpacePressed;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Input|Action", Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> IA_SpaceReleased;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Input|Action", Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> IA_OnePressed;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Input|Action", Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> IA_TwoPressed;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Input|Action", Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> IA_ThreePressed;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Input|Action", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> IA_Turn;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Input|Action", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> IA_LookUp;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Input|Action", Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> IA_EPressed;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Input|Action", Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> IA_LeftArrowPressed;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Input|Action", Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> IA_RightArrowPressed;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Input|Action", Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> IA_UpArrowPressed;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Input|Action", Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> IA_DownArrowPressed;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Input|Action", Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> IA_PPressed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Controller Properties|SpaceShip", Meta = (AllowPrivateAccess = "true"))
	float SpaceShipLookUpRate;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Controller Properties|SpaceShip", Meta = (AllowPrivateAccess = "true"))
	float SpaceShipTurnRate;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Controller Properties|IT", Meta = (AllowPrivateAccess = "true"))
	float ITLookUpRate;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Controller Properties|IT", Meta = (AllowPrivateAccess = "true"))
	float ITTurnRate;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Controller Properties|IF", Meta = (AllowPrivateAccess = "true"))
	float IFLookUpRate;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Controller Properties|IF", Meta = (AllowPrivateAccess = "true"))
	float IFTurnRate;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Controller Properties|OT", Meta = (AllowPrivateAccess = "true"))
	float OTLookUpRate;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Controller Properties|OT", Meta = (AllowPrivateAccess = "true"))
	float OTTurnRate;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Controller Info", Meta = (AllowPrivateAccess = "true"))
	bool bAllowTurnLookup;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera Properties|SpaceShip", Meta = (AllowPrivateAccess = "true"))
	float SpaceShipMaxAngle;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera Properties|SpaceShip", Meta = (AllowPrivateAccess = "true"))
	float SpaceShipDeadZoneAngle;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera Properties|SpaceShip", Meta = (AllowPrivateAccess = "true"))
	float SpaceShipDeadZoneRate;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera Properties|SpaceShip", Meta = (AllowPrivateAccess = "true"))
	float SpaceShipDeadZoneSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera Properties|IT", Meta = (AllowPrivateAccess = "true"))
	float ITMaxAngle;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera Properties|IT", Meta = (AllowPrivateAccess = "true"))
	float ITDeadZoneAngle;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera Properties|IT", Meta = (AllowPrivateAccess = "true"))
	float ITDeadZoneRate;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera Properties|IT", Meta = (AllowPrivateAccess = "true"))
	float ITDeadZoneSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera Properties|IF", Meta = (AllowPrivateAccess = "true"))
	float IFMaxAngle;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera Properties|IF", Meta = (AllowPrivateAccess = "true"))
	float IFDeadZoneAngle;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera Properties|IF", Meta = (AllowPrivateAccess = "true"))
	float IFDeadZoneRate;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera Properties|IF", Meta = (AllowPrivateAccess = "true"))
	float IFDeadZoneSpeed;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Controller State", Meta = (AllowPrivateAccess = "true"))
	EControllerState ControllerState;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Controller State", Meta = (AllowPrivateAccess = "true"))
	EControlViewState ControlViewState;;
public:
	ARTFController();

	static ARTFController* GetInstance();
	
	virtual void SetupInputComponent() override;
	virtual void Tick(float DeltaSeconds) override;
	
	UFUNCTION(BlueprintCallable)
	void InitControllerInfo(APawn* SpaceShip);
	
	UFUNCTION(BlueprintCallable)
	AMainCharacter* GetMainCharacter() const;
	UFUNCTION(BlueprintCallable)
	AMainSpaceShip* GetMainSpaceShip() const;
	
	UFUNCTION(BlueprintCallable)
	EControllerState GetControllerState() const;
	UFUNCTION(BlueprintCallable)
	void SetControllerState(EControllerState NewState);
	UFUNCTION(BlueprintCallable)
	EControlViewState GetControlViewState() const;
	UFUNCTION(BlueprintCallable)
	void SetControlViewState(EControlViewState NewState);

	UFUNCTION()
	void OnWAxis(const FInputActionValue& InputActionValue);
	UFUNCTION()
	void OnDAxis(const FInputActionValue& InputActionValue);
	UFUNCTION()
	void OnShiftPressed();
	UFUNCTION()
	void OnShiftReleased();
	UFUNCTION()
	void OnSpacePressed();
	UFUNCTION()
	void OnSpaceReleased();
	UFUNCTION()
	void OnOnePressed();
	UFUNCTION()
	void OnTwoPressed();
	UFUNCTION()
	void OnThreePressed();
	UFUNCTION()
	void OnTurn(const FInputActionValue& InputActionValue);
	UFUNCTION()
	void OnLookUp(const FInputActionValue& InputActionValue);
	UFUNCTION()
	void OnEPressed();
	UFUNCTION()
	void OnLeftArrowPressed();
	UFUNCTION()
	void OnRightArrowPressed();
	UFUNCTION()
	void OnUpArrowPressed();
	UFUNCTION()
	void OnDownArrowPressed();
	UFUNCTION()
	void OnPPressed();

	void ToSpaceShipControl();
	void ToITControl();
	void ToIFControl();
	void ToOTControl();

	void ViewOnTurn(const float InputScale, const float TurnRate, const bool bDeadZone = false, const float DeadZoneAngle = 0.0f, const float DeadZoneRate = 0.0f, const float MaxAngle = 0.0f);
	void ViewOnLookUp(const float InputScale, const float LookupRate, const bool bDeadZone = false, const float DeadZoneAngle = 0.0f, const float DeadZoneRate = 0.0f, const float MaxAngle = 0.0f);
	void BlockTurnAndLook();
	void OpenTurnAndLook();
	void EscapeDeadZone();
	void EscapeDeadZoneImpl(const float DeadZoneAngle, const float DeadZoneSpeed);
	float MapControlRotation(const float Angle) const;

	bool CanSpaceShipInputMove() const;
	bool CanCharacterInputMove() const;
	bool CanChangeControlState(EControllerState NewState) const;
	bool CanGetOffSpaceShip() const;
	bool CanGetOnSpaceShip() const;
	bool CanCacheSpaceShipCamera() const;
	bool CanTurnAndLook() const;
};
