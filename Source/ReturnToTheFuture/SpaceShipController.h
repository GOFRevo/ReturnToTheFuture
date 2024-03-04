// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SpaceShipController.generated.h"

class UInputMappingContext;
class UInputAction;
/**
 * 
 */
UCLASS()
class RETURNTOTHEFUTURE_API ASpaceShipController : public APlayerController
{
	GENERATED_BODY()
private:
	UPROPERTY()
	class ASpaceShipCameraManager* SpaceShipCameraManager;
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Controller Info", Meta = (AllowPrivateAccess))
	class AMainSpaceShip* MainSpaceShip;
	
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
public:
	ASpaceShipController();
	virtual void OnPossess(APawn* SpaceShip) override;

	virtual void SetupInputComponent() override;

	void OnMoveForwardBegin();
	
	void OnMoveForwardEnd();
	
	void OnMoveBackBegin();
	
	void OnMoveBackEnd();
};
