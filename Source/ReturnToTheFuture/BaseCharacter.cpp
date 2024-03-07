// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacter.h"

#include "Kismet/KismetMathLibrary.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

FVector ABaseCharacter::GetControlForwardVector() const
{
	const FRotator InRot{0.0f, GetControlRotation().Yaw, 0.0f};
	return UKismetMathLibrary::GetForwardVector(InRot);
}

FVector ABaseCharacter::GetControlRightVector() const
{
	const FRotator InRot{0.0f, GetControlRotation().Yaw, 0.0f};
	return UKismetMathLibrary::GetRightVector(InRot);
}

void ABaseCharacter::PlayMovementInput(bool InForwardAxis, float ScaleValue)
{
	if(InForwardAxis)
	{
		AddMovementInput(GetControlForwardVector(), ScaleValue);
	}else
	{
		AddMovementInput(GetControlRightVector(), ScaleValue);
	}
}


