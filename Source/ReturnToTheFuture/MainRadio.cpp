// Fill out your copyright notice in the Description page of Project Settings.


#include "MainRadio.h"
#include "Components/AudioComponent.h"

AMainRadio::AMainRadio()
{
	Audio = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComponent"));
	SetRootComponent(Audio);
}

void AMainRadio::Init(bool bAutoStart)
{
	Super::Init(bAutoStart);
}

void AMainRadio::OpenDevice()
{
}

void AMainRadio::CloseDevice()
{
}

void AMainRadio::Play()
{
}

void AMainRadio::Stop()
{
}