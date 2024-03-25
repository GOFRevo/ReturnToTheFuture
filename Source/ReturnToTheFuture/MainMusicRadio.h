// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MainRadio.h"
#include "MusicRadioEnums.h"
#include "MusicRadioStruct.h"
#include "MainMusicRadio.generated.h"
/**
 * 
 */
class UMusicData;
class UWidgetComponent;
UCLASS()
class RETURNTOTHEFUTURE_API AMainMusicRadio : public AMainRadio
{
	GENERATED_BODY()
private:
	bool bIsOpened;
	EMusicRadioState MusicRadioState;
	FString MusicFolderPath;
	
	TArray<FString> ChannelName;
	TArray<uint64_t> MusicOfChannelCache;
	uint64_t ChannelIndex;
	
	TArray<FString> MusicFullName;
	uint64_t MusicIndex;
	
	UPROPERTY()
	UMusicData* MusicData;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget", Meta = (AllowPrivateAccess = "true"))
	UWidgetComponent* RadioWidget;
public:
	AMainMusicRadio();

	void BeginPlay() override;
	void Tick(float DeltaTime) override;
	
	void UpdateMusicRadioState(UMusicData* MD);

	void Init(bool bAutoStart) override;
	void OpenDevice() override;
	void CloseDevice() override;
	
	void Play() override;
	void Pause() override;
	
	bool FindChannelOfMusic(bool bOrder, bool bChangeSongIndex);
	uint64_t GetNextMusicModIndex() const;
	uint64_t GetLastMusicModIndex() const;
	void ModNextChannelModIndex();
	void ModLastChannelModIndex();
	
	void ChangeMusic(bool bOrder);
	void ChangeChannel(bool bOrder);
	void LoadNewMusic(bool bAutoStart);
	void AutoNext();
	
	bool LoadChannels();
	bool LoadMusicsFromChannel();
	
	bool IsValid() const{ return MusicRadioState != EMusicRadioState::EMRS_Invalid; }
	virtual bool IsOpened() override;
	virtual bool IsPlaying() override;
	bool IsPaused();
	EMusicRadioState GetMusicRadioState() const;
	UFUNCTION(BlueprintCallable)
	FMusicRadioInfo GetMusicRadioInfo() const;
};
