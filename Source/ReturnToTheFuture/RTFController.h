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
	TObjectPtr<UInputAction> IA_MoveForwardPressed;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Input|Action", Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> IA_MoveBackPressed;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Input|Action", Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> IA_MoveForwardReleased;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Input|Action", Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> IA_MoveBackReleased;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Input|Action", Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> IA_SpaceShipView;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Input|Action", Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> IA_ITView;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Input|Action", Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> IA_IFView;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Input|Action", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> IA_Turn;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Input|Action", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> IA_LookUp;

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
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Controller Info", Meta = (AllowPrivateAccess = "true"))
	EControllerState ControllerState;
public:
	ARTFController();

	static ARTFController* GetInstance();
	
	virtual void SetupInputComponent() override;
	
	UFUNCTION(BlueprintCallable)
	void InitControllerInfo(APawn* SpaceShip);
	UFUNCTION(BlueprintCallable)
	EControllerState GetControllerState() const;
	UFUNCTION(BlueprintCallable)
	void SetControllerState(EControllerState NewState);
	UFUNCTION(BlueprintCallable)
	AMainCharacter* GetMainCharacter() const;
	UFUNCTION(BlueprintCallable)
	AMainSpaceShip* GetMainSpaceShip() const;

	UFUNCTION()
	void OnBeginMoveForward(const FInputActionValue& InputActionValue);
	UFUNCTION()
	void OnEndMoveForward(const FInputActionValue& InputActionValue);
	UFUNCTION()
	void OnBeginMoveBack(const FInputActionValue& InputActionValue);
	UFUNCTION()
	void OnEndMoveBack(const FInputActionValue& InputActionValue);

	void ToSpaceShipView();
	void ToITView();
	void ToIFView();

	UFUNCTION()
	void OnTurn(const FInputActionValue& InputActionValue);
	UFUNCTION()
	void OnLookUp(const FInputActionValue& InputActionValue);

	bool IsCharacterOnSpaceShip() const;

	void SpaceShipOnTurn(const float InputScale);
	void SpaceShipOnLookUp(const float InputScale);
	void ITOnTurn(const float InputScale);
	void ITOnLookUp(const float InputScale);
	void IFOnTurn(const float InputScale);
	void IFOnLookUp(const float InputScale);
};
