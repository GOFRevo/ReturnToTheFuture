// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MainRadio.h"
#include "MainMusicRadio.generated.h"

/**
 * 
 */
USTRUCT(Blueprintable)
struct FSongData
{
	GENERATED_BODY()

	UPROPERTY()
	USoundWave* SoundWave = nullptr;
	bool bIsOn = false;
	float StartTime = 0.0f;
	float TotalTime = 0.0f;
};

UCLASS()
class RETURNTOTHEFUTURE_API AMainMusicRadio : public AMainRadio
{
	GENERATED_BODY()
private:
	FString MusicFolderPath;

	bool bGood;
	TArray<FString> ChannelName;
	TArray<uint64_t> ChannelChangeIndex;
	uint64_t CurrentChannelIndex;
	TArray<FString> SongPath;
	uint64_t CurrentSongIndex;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SongData", Meta = (AllowPrivateAccess = "true"))
	FSongData SongData;
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USoundWave* Debug;
	
	AMainMusicRadio();

	void BeginPlay() override;
	void Tick(float DeltaTime) override;

	void Init(bool bStart) override;
	void Start() override;
	void End() override;
	void Play(bool bNew) override;
	void Stop() override;
	
	void ChangeSongImpl(bool bNext);
	bool ChangeChannelImpl(bool bNext, bool bChangeSongIndex);
	uint64_t ModNextSongIndex() const;
	void ModNextChannelIndex();
	uint64_t ModLastSongIndex() const;
	void ModLastChannelIndex();
	
	void ChangeSong(bool bNext);
	void ChangeChannel(bool bNext);
	
	bool LoadChannels();
	bool LoadSongFromChannel();
	bool LoadSongData();
};
