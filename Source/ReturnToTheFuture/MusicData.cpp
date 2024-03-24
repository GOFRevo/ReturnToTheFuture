#include "MusicData.h"
#include "Components/AudioComponent.h"

UMusicData::UMusicData():
	RuntimeImporter(nullptr),
	AudioComp(nullptr),
	SoundWave(nullptr),
	MusicDataState(EMusicDataState::EMDS_IsLoading),
	bAutoStart(false),
	bIsValid(false),
	StartTime(0.0f),
	TotalTime(0.0f)
{}

void UMusicData::Init(UAudioComponent* Audio)
{
	check(Audio != nullptr)
	AudioComp = Audio;
	RuntimeImporter = URuntimeAudioImporterLibrary::CreateRuntimeAudioImporter();
	RuntimeImporter->OnResult.AddDynamic(this, &UMusicData::OnLoadResult);
	OnMetaResultDelegate.BindDynamic(this, &UMusicData::OnMetaResult);
}

UMusicData* UMusicData::CreateMusicData(UAudioComponent* Audio)
{
	UMusicData* Result = NewObject<UMusicData>();
	Result->Init(Audio);
	return Result;
}

void UMusicData::LoadMusic(const FString& MusicPath, bool AutoStart)
{
	MusicDataState = EMusicDataState::EMDS_IsLoading;
	bAutoStart = AutoStart;
	RuntimeImporter->ImportAudioFromFile(MusicPath, ERuntimeAudioFormat::Auto);
}

void UMusicData::MusicTick(float DeltaTime)
{
	if(MusicDataState == EMusicDataState::EMDS_IsPlaying)
	{
		StartTime += DeltaTime;
		if(StartTime >= TotalTime) MusicDataState = EMusicDataState::EMDS_HasComplete;
	}
}

void UMusicData::Play(){
	if(MusicDataState != EMusicDataState::EMDS_IsStopping) return;
	AudioComp->SetFloatParameter(TEXT("StartTime"), StartTime);
	AudioComp->SetWaveParameter(TEXT("Music"), SoundWave);
	AudioComp->Play();
	MusicDataState = EMusicDataState::EMDS_IsPlaying;
}

void UMusicData::Stop()
{
	if(!CanStop()) return;
	AudioComp->Stop();
	MusicDataState = EMusicDataState::EMDS_IsStopping;
}

void UMusicData::ClearState()
{
	StartTime = 0.0f;
	MusicDataState = EMusicDataState::EMDS_IsStopping;
}

void UMusicData::ClearResource()
{
	SoundWave = nullptr;
	bIsValid = false;
	bAutoStart = false;
	StartTime = 0.0f;
	TotalTime = 0.0f;
	MusicDataState = EMusicDataState::EMDS_IsLoading;
}

void UMusicData::SetValid(bool IsValid)
{
	bIsValid = IsValid;
}

bool UMusicData::IsValid() const
{
	return bIsValid;
}

bool UMusicData::IsPlaying() const
{
	return MusicDataState == EMusicDataState::EMDS_IsPlaying;
}

bool UMusicData::HasComplete() const
{
	return MusicDataState == EMusicDataState::EMDS_HasComplete;
}

bool UMusicData::CanStop() const
{
	return MusicDataState == EMusicDataState::EMDS_IsPlaying ||
		MusicDataState == EMusicDataState::EMDS_HasComplete;
}


