#include "MusicData.h"
#include "RTFLoader.h"
#include "Components/AudioComponent.h"

UMusicData::UMusicData():
	AudioComp(nullptr),
	SoundWave(nullptr),
	MusicDataState(EMusicDataState::EMDS_InValid),
	StartTime(0.0f),
	TotalTime(0.0f)
{}

UMusicData* UMusicData::CreateMusicData(UAudioComponent* Audio)
{
	UMusicData* Result = NewObject<UMusicData>();
	Result->AudioComp = Audio;
	return Result;
}

void UMusicData::LoadMusic(const FString& MusicPath, bool AutoStart)
{
	if(!CanLoad()) return;
	MusicDataState = EMusicDataState::EMDS_Loading;
	Clear();
	SoundWave = FRTFLoader::LoadSoundWaveFromFile(MusicPath);
	if(SoundWave == nullptr)
	{
		MusicDataState = EMusicDataState::EMDS_InValid;
	}
	else
	{
		TotalTime = SoundWave->GetDuration();
		MusicDataState = EMusicDataState::EMDS_LoadComplete;
		if(AutoStart) Play();
	}
}

void UMusicData::MusicTick(float DeltaTime)
{
	if(MusicDataState == EMusicDataState::EMDS_Playing)
	{
		StartTime += DeltaTime;
		if(StartTime >= TotalTime) MusicDataState = EMusicDataState::EMDS_PlayComplete;
	}
}

void UMusicData::Pause(bool bShouldPause)
{
	if(!CanPause(bShouldPause)) return;
	AudioComp->SetPaused(bShouldPause);
	if(bShouldPause) MusicDataState = EMusicDataState::EMDS_Paused;
	else MusicDataState = EMusicDataState::EMDS_Playing;
}

void UMusicData::Play(){
	if(MusicDataState != EMusicDataState::EMDS_LoadComplete) return;
	AudioComp->SetWaveParameter(TEXT("Music"), SoundWave);
	AudioComp->Play();
	AudioComp->SetPaused(false);
	MusicDataState = EMusicDataState::EMDS_Playing;
}

void UMusicData::Stop()
{
	if(!CanStop()) return;
	AudioComp->Stop();
	MusicDataState = EMusicDataState::EMDS_Stopped;
}

void UMusicData::Clear()
{
	SoundWave = nullptr;
	StartTime = 0.0f;
	TotalTime = 0.0f;
}

bool UMusicData::IsPlaying() const
{
	return MusicDataState == EMusicDataState::EMDS_Playing;
}

bool UMusicData::IsPaused() const
{
	return MusicDataState == EMusicDataState::EMDS_Paused;
}

bool UMusicData::HasPlayComplete() const
{
	return MusicDataState == EMusicDataState::EMDS_PlayComplete;
}

bool UMusicData::HasLoadComplete() const
{
	return MusicDataState == EMusicDataState::EMDS_LoadComplete;
}

bool UMusicData::CanPause(bool bShouldPause) const
{
	if(bShouldPause) return MusicDataState == EMusicDataState::EMDS_Playing;
	return MusicDataState == EMusicDataState::EMDS_Paused;
}

bool UMusicData::CanStop() const
{
	return MusicDataState != EMusicDataState::EMDS_InValid &&
		MusicDataState != EMusicDataState::EMDS_Stopped &&
		MusicDataState != EMusicDataState::EMDS_Loading;
}

bool UMusicData::CanLoad() const
{
	return MusicDataState == EMusicDataState::EMDS_InValid || MusicDataState == EMusicDataState::EMDS_Stopped;
}

EMusicDataState UMusicData::GetMusicDataState() const
{
	return MusicDataState;
}
