#pragma once
#include "CoreMinimal.h"
#include "MusicRadioEnums.h"
#include "MusicRadioStruct.h"
#include "MusicData.generated.h"

UCLASS()
class UMusicData: public UObject
{
	GENERATED_BODY()
private:
	UPROPERTY()
	UMusicTimeLine* DefaultMusicTimeLine;
	UPROPERTY()
	UAudioComponent* AudioComp;
	UPROPERTY()
	USoundWave* SoundWave;
	UPROPERTY()
	UMusicLRC* MusicLRC;
	
	EMusicDataState MusicDataState;
	float StartTime;
	float TotalTime;
	bool bFirstTimeline;
	
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
	const FString& GetMusicName() const;
	UMusicTimeLine* GetMusicTimeLine();
	bool IsFirstTimeLine() const;
	bool CanGetMusicTimeLine() const;
	float GetMusicStartTime() const;
};