// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharacter.h"
#include "MainMusicRadio.h"
#include "RTFCameraManager.h"
#include "MainSpaceShip.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

AMainCharacter::AMainCharacter():
	CharacterMainState(ECharacterMainState::ECMS_OnSpaceShip),
	ITCameraFOV(90.0f),
	IFCameraFOV(90.0f),
	OTCameraFOV(90.0f),
	IFCameraPivotTarget(nullptr)
{
	IFCameraPivotTarget = CreateDefaultSubobject<USceneComponent>(FName("IFCameraPivotTarget"));
	IFCameraPivotTarget->SetupAttachment(RootComponent);
}

void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();
	GetCharacterMovement()->GravityScale = 0.0f;
}

ECharacterMainState AMainCharacter::GetCharacterMainState() const
{
	return CharacterMainState;
}

void AMainCharacter::SetCharacterMainState(ECharacterMainState NewState)
{
	CharacterMainState = NewState;
}

void AMainCharacter::CalcCamera(float DeltaTime, FMinimalViewInfo& OutResult)
{
	ARTFCameraManager::GetInstance()->CustomCamera(DeltaTime, OutResult);
}

void AMainCharacter::BeginMoveSpaceShipForward(AMainSpaceShip* SpaceShip)
{
	SpaceShip->BeginMoveForward();
}

void AMainCharacter::EndMoveSpaceShipForward(AMainSpaceShip* SpaceShip)
{
	SpaceShip->EndMoveForward();
}

void AMainCharacter::BeginMoveSpaceShipBack(AMainSpaceShip* SpaceShip)
{
	SpaceShip->BeginMoveBack();
}

void AMainCharacter::EndMoveSpaceShipBack(AMainSpaceShip* SpaceShip)
{
	SpaceShip->EndMoveBack();
}

void AMainCharacter::MoveSpaceShipHorizon(AMainSpaceShip* SpaceShip, float Scale)
{
	SpaceShip->MoveHorizon(Scale);
}

void AMainCharacter::MoveSpaceShipVertical(AMainSpaceShip* SpaceShip, float Scale)
{
	SpaceShip->MoveVertical(Scale);
}

void AMainCharacter::GetOffSpaceShip(AMainSpaceShip* SpaceShip)
{
	DetachFromSpaceShip(SpaceShip);
	SetActorLocation(SpaceShip->GetActorLocation() + FVector{0.0f, 140.0f, 20.0f});
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Pawn"), true);
	GetCharacterMovement()->GravityScale = 1.0f;
	SetCharacterMainState(ECharacterMainState::ECMS_OnSpaceStation);
}

void AMainCharacter::GetOnSpaceShip(AMainSpaceShip* SpaceShip)
{
	GetCharacterMovement()->GravityScale = 0.0f;
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("NoCollision"), true);
	SetActorLocation(SpaceShip->GetActorLocation() + FVector{100.0f, 0.0f, 100.0f});
	AttachToSpaceShip(SpaceShip);
	SetCharacterMainState(ECharacterMainState::ECMS_OnSpaceShip);
}

void AMainCharacter::AttachToSpaceShip(AMainSpaceShip* SpaceShip)
{
	const FAttachmentTransformRules Rules{EAttachmentRule::KeepWorld, true};
	AttachToActor(SpaceShip, Rules);
}

void AMainCharacter::DetachFromSpaceShip(AMainSpaceShip* SpaceShip)
{
	const FDetachmentTransformRules Rules{EDetachmentRule::KeepWorld, false};
	DetachFromActor(Rules);
}

FTransform AMainCharacter::GetIFPivotTargetTransform() const
{
	return IFCameraPivotTarget->GetComponentTransform();
}

void AMainCharacter::ChangeMusicRadioChannel(AMainMusicRadio* MusicRadio, bool bOrder)
{
	MusicRadio->ChangeChannel(bOrder);
}

void AMainCharacter::ChangeMusicRadioMusic(AMainMusicRadio* MusicRadio, bool bOrder)
{
	MusicRadio->ChangeMusic(bOrder);
}

void AMainCharacter::StopRadio(AMainRadio* Radio)
{
	Radio->Stop();
}

void AMainCharacter::PlayRadio(AMainRadio* Radio)
{
	Radio->Play();
}

bool AMainCharacter::IsOnSpaceShip() const
{
	return CharacterMainState == ECharacterMainState::ECMS_OnSpaceShip;
}
