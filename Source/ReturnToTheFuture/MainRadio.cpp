// Fill out your copyright notice in the Description page of Project Settings.


#include "MainRadio.h"
#include "Components/AudioComponent.h"

AMainRadio::AMainRadio()
{
	Audio = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComponent"));
	SetRootComponent(Audio);
}

void AMainRadio::Init(bool bStart)
{
	Super::Init(bStart);
}

void AMainRadio::Start()
{
	Super::Start();
}

void AMainRadio::End()
{
	Super::End();
}

void AMainRadio::Play(bool bNew)
{
}

void AMainRadio::Stop()
{
}