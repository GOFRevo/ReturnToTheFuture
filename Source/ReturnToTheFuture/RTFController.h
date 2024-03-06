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
	
	void OnBeginMoveForward();
	void OnEndMoveForward();
	void OnBeginMoveBack();
	void OnEndMoveBack();

	void ToSpaceShipView();
	void ToITView();

	bool IsCharacterOnSpaceShip() const;
};
