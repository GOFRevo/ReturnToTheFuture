#pragma once
#include "CoreMinimal.h"
#include "MusicRadioEnums.h"
#include "RuntimeAudioImporterLibrary.h"
#include "MusicData.generated.h"

UCLASS()
class UMusicData: public UObject
{
	GENERATED_BODY()
private:
	UPROPERTY()
	FOnPrepareSoundWaveForMetaSoundsResult OnMetaResultDelegate;
	UPROPERTY()
	URuntimeAudioImporterLibrary* RuntimeImporter;
	UPROPERTY()
	UAudioComponent* AudioComp;
	UPROPERTY()
	UImportedSoundWave* SoundWave;

	EMusicDataState MusicDataState;
	TAtomic<bool> bAutoStart;
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
		MusicDataState = EMusicDataState::EMDS_IsStopping;
		FPlatformMisc::MemoryBarrier();
		if(bAutoStart && bIsValid) Play();
	}
	void Init(UAudioComponent* Audio);
public:
	UMusicData();
	static UMusicData* CreateMusicData(UAudioComponent* Audio);
	void LoadMusic(const FString& MusicPath, bool AutoStart);
	// Only In Actor::Tick Is Useful!
	void MusicTick(float DeltaTime);
	void Play();
	void Stop();
	//Use For ReStart Play
	void ClearState();
	//Use For LoadMusic 
	void ClearResource();

	void SetValid(bool IsValid);
	bool IsValid() const;
	bool IsPlaying() const;
	bool HasComplete() const;
	bool CanStop() const;
	EMusicDataState GetMusicDataState() const;
};