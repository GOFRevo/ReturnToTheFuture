// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MainDevice.h"
#include "MainRadio.generated.h"

/**
 * 
 */
class UWidgetComponent;
UCLASS()
class RETURNTOTHEFUTURE_API AMainRadio : public AMainDevice
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio", Meta = (AllowPrivateAccess = "true"))
	UAudioComponent* Audio;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget", Meta = (AllowPrivateAccess = "true"))
	UWidgetComponent* RadioWidget;
public:
	AMainRadio();

	virtual void Init(bool bAutoStart) override;
	virtual void OpenDevice() override;
	virtual void CloseDevice() override;
	virtual void Play();
	virtual void Stop();

	virtual bool IsPlaying();
	virtual bool IsOpened();
};
