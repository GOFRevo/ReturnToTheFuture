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
public:
	AMainMusicRadio();

	void BeginPlay() override;
	void Tick(float DeltaTime) override;
	
	void UpdateMusicRadioState(UMusicData* MD);

	void Init(bool bAutoStart) override;
	void OpenDevice() override;
	void CloseDevice() override;
	
	void Play() override;
	void Stop() override;
	
	bool FindChannelOfMusic(bool bOrder, bool bChangeSongIndex);
	uint64_t GetNextMusicModIndex() const;
	uint64_t GetLastMusicModIndex() const;
	void ModNextChannelModIndex();
	void ModLastChannelModIndex();
	
	void ChangeMusic(bool bOrder);
	void ChangeChannel(bool bOrder);
	bool PreLoadNewMusic();
	void PostLoadNewMusic(bool bAutoStart);
	void AutoNext();
	
	bool LoadChannels();
	bool LoadMusicsFromChannel();
	
	bool IsValid() const{ return MusicRadioState != EMusicRadioState::EMRS_Invalid; }
	virtual bool IsPlaying() override;
	virtual bool IsOpened() override;
	EMusicRadioState GetMusicRadioState() const;
	bool CanStop() const;
	bool CanPlay() const;
	UFUNCTION(BlueprintCallable)
	FMusicRadioInfo GetMusicRadioInfo() const;
};
