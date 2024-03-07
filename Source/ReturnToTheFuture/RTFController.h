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
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Controller State", Meta = (AllowPrivateAccess = "true"))
	EControllerState ControllerState;
public:
	ARTFController();

	static ARTFController* GetInstance();
	
	virtual void SetupInputComponent() override;
	
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

	void ToSpaceShipView();
	void ToITView();
	void ToIFView();
	void ToOTView();

	void SpaceShipOnTurn(const float InputScale);
	void SpaceShipOnLookUp(const float InputScale);
	void ITOnTurn(const float InputScale);
	void ITOnLookUp(const float InputScale);
	void IFOnTurn(const float InputScale);
	void IFOnLookUp(const float InputScale);
	void OTOnTurn(const float InputScale);
	void OTOnLookUp(const float InputScale);

	bool CanSpaceShipInputMove() const;
	bool CanCharacterInputMove() const;
	bool CanChangeView(EControllerState NewState) const;
	bool CanGetOffSpaceShip() const;
	bool CanGetOnSpaceShip() const;
};
