// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MainRadio.h"
#include "RuntimeAudioImporterLibrary.h"
#include "MainMusicRadio.generated.h"

/**
 * 
 */
UCLASS()
class UMusicData: public UObject
{
	GENERATED_BODY()
private:
	UPROPERTY()
	FOnPrepareSoundWaveForMetaSoundsResult OnMetaResultDelegate;
	UPROPERTY()
	UImportedSoundWave* SoundWave;
	UPROPERTY()
	URuntimeAudioImporterLibrary* RuntimeImporter;
	UPROPERTY()
	UAudioComponent* AudioComp;
	bool bAutoStart;
	TAtomic<bool> bIsPlaying;
	TAtomic<bool> bIsValid;
	float StartTime;
	float TotalTime;
private:
	UFUNCTION()
	void OnLoadResult(URuntimeAudioImporterLibrary* Importer, UImportedSoundWave* ImportedSoundWave, ERuntimeImportStatus Status)
	{
		if(Status != ERuntimeImportStatus::SuccessfulImport) return;
		SoundWave = ImportedSoundWave;
		ImportedSoundWave->PrepareSoundWaveForMetaSounds(OnMetaResultDelegate);
	}
	UFUNCTION()
	void OnMetaResult(bool bSuccess)
	{
		if(!bSuccess) return;
		StartTime = 0.0f;
		TotalTime = SoundWave->GetDuration();
		bIsValid = true;
		FPlatformMisc::MemoryBarrier();
		if(bAutoStart) Play();
	}
	void Init(const FString& MusicPath, UAudioComponent* Audio, bool AutoStart);
public:
	UMusicData();
	static UMusicData* CreateMusicData(const FString& MusicPath, UAudioComponent* Audio, bool AutoStart);
	void LoadMusic(const FString& MusicPath, bool AutoStart);
	// Only In Actor::Tick Is Useful!
	void MusicTick(float DeltaTime);
	void Play();
	void Stop();
	//Use For ReStart Play
	void ClearState();
	//Use For LoadMusic 
	void ClearResource();

	bool IsValid() const { return bIsValid; }
	bool IsPlaying() const { return bIsPlaying; }
};

UCLASS()
class RETURNTOTHEFUTURE_API AMainMusicRadio : public AMainRadio
{
	GENERATED_BODY()
private:
	bool bIsValid;
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

	bool IsValid() const{ return bIsValid && MusicData->IsValid(); }
	virtual bool IsPlaying() override{ return MusicData->IsPlaying(); }

	void BeginPlay() override;
	void Tick(float DeltaTime) override;

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
	
	bool LoadChannels();
	bool LoadMusicsFromChannel();
};
