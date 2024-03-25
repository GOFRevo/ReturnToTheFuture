#pragma once
#include "CoreMinimal.h"
#include "MusicRadioEnums.h"
#include "MusicData.generated.h"

UCLASS()
class UMusicData: public UObject
{
	GENERATED_BODY()
private:
	UPROPERTY()
	UAudioComponent* AudioComp;
	UPROPERTY()
	USoundWave* SoundWave;
	EMusicDataState MusicDataState;
	float StartTime;
	float TotalTime;
	
	void Clear();
	bool CanPause(bool bShouldPause) const;
	bool CanStop() const;
	bool CanLoad() const;
public:
	UMusicData();
	static UMusicData* CreateMusicData(UAudioComponent* Audio);
	void LoadMusic(const FString& MusicPath, bool AutoStart);
	// Only In Actor::Tick Is Useful!
	void MusicTick(float DeltaTime);
	void Pause(bool bShouldPause);
	// Play New Music
	void Play();
	// Stop Old Music
	void Stop();

	bool IsPlaying() const;
	bool IsPaused() const;
	bool HasPlayComplete() const;
	bool HasLoadComplete() const;
	EMusicDataState GetMusicDataState() const;
};