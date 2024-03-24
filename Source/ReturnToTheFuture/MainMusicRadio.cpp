// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMusicRadio.h"

#include <thread>

#include "Components/AudioComponent.h"
#include "RTFInfo.h"

UMusicData::UMusicData():
	SoundWave(nullptr),
	RuntimeImporter(nullptr),
	AudioComp(nullptr),
	bAutoStart(false),
	bIsPlaying(false),
	bIsValid(false),
	StartTime(0.0f),
	TotalTime(0.0f)
{}

void UMusicData::Init(const FString& MusicPath, UAudioComponent* Audio, bool AutoStart)
{
	check(Audio != nullptr)
	AudioComp = Audio;
	RuntimeImporter = URuntimeAudioImporterLibrary::CreateRuntimeAudioImporter();
	RuntimeImporter->OnResult.AddDynamic(this, &UMusicData::OnLoadResult);
	OnMetaResultDelegate.BindDynamic(this, &UMusicData::OnMetaResult);

	LoadMusic(MusicPath, AutoStart);
}

UMusicData* UMusicData::CreateMusicData(const FString& MusicPath, UAudioComponent* Audio, bool AutoStart)
{
	UMusicData* Result = NewObject<UMusicData>();
	Result->Init(MusicPath, Audio, AutoStart);
	return Result;
}

void UMusicData::LoadMusic(const FString& MusicPath, bool AutoStart)
{
	bAutoStart = AutoStart;
	RuntimeImporter->ImportAudioFromFile(MusicPath, ERuntimeAudioFormat::Auto);
}

void UMusicData::MusicTick(float DeltaTime)
{
	if(bIsPlaying && bIsValid) StartTime += DeltaTime;
}

void UMusicData::Play(){
	if(bIsPlaying) return;
	while(!bIsValid) std::this_thread::yield();
	AudioComp->SetWaveParameter(TEXT("Music"), SoundWave);
	AudioComp->SetFloatParameter(TEXT("TotalTime"), TotalTime);
	AudioComp->SetFloatParameter(TEXT("StartTime"), StartTime);
	AudioComp->Play();
	bIsPlaying = true;
}

void UMusicData::Stop()
{
	if(!bIsPlaying || !bIsValid) return;
	bIsPlaying = false;
	AudioComp->Stop();
}

void UMusicData::ClearState()
{
	StartTime = 0.0f;
}

void UMusicData::ClearResource()
{
	ClearState();
	bAutoStart = false;
	bIsPlaying = false;
	bIsValid = false;
	TotalTime = 0.0f;
}

AMainMusicRadio::AMainMusicRadio():
	bIsValid(false),
	ChannelIndex(0),
	MusicIndex(0),
	MusicData(nullptr)
{
	MusicFolderPath = FRTFInfo::ResourcePath / "Music";
}

void AMainMusicRadio::BeginPlay()
{
	Super::BeginPlay();
	
	bIsValid = LoadChannels() && LoadMusicsFromChannel() && FindChannelOfMusic(true, false);
	if(!bIsValid) return;

	const FString MusicPath = MusicFolderPath / ChannelName[ChannelIndex] / MusicFullName[MusicIndex];
	MusicData = UMusicData::CreateMusicData(MusicPath, Audio, true);
}

void AMainMusicRadio::Tick(float DeltaTime)
{
	MusicData->MusicTick(DeltaTime);
}

void AMainMusicRadio::Init(bool bAutoStart)
{
}

void AMainMusicRadio::OpenDevice()
{
}

void AMainMusicRadio::CloseDevice()
{
}

void AMainMusicRadio::Play()
{
}

void AMainMusicRadio::Stop()
{
}

bool AMainMusicRadio::FindChannelOfMusic(bool bOrder, bool bCacheMusicOfChannel){
	if(ChannelName.Num() == 1) return !MusicFullName.IsEmpty();
	const uint64_t OldChannelIndex = ChannelIndex;
	while(true)
	{
		if(bOrder) ModNextChannelModIndex();
		else ModLastChannelModIndex();
		
		if(LoadMusicsFromChannel())
		{
			if(bCacheMusicOfChannel)
			{
				MusicOfChannelCache[OldChannelIndex] = MusicIndex;
				MusicIndex = MusicOfChannelCache[ChannelIndex];
			}
			return true;
		}
		if(ChannelIndex == OldChannelIndex) return false;
	}
}

uint64_t AMainMusicRadio::GetNextMusicModIndex() const
{
	return (MusicIndex + 1) % MusicFullName.Num();
}

uint64_t AMainMusicRadio::GetLastMusicModIndex() const
{
	return MusicIndex == 0? MusicFullName.Num() - 1: MusicIndex - 1;
}

void AMainMusicRadio::ModNextChannelModIndex()
{
	ChannelIndex = (ChannelIndex + 1) % ChannelName.Num();
}

void AMainMusicRadio::ModLastChannelModIndex()
{
	ChannelIndex = ChannelIndex == 0? ChannelName.Num() - 1: ChannelIndex - 1;
}

void AMainMusicRadio::ChangeSong(bool bOrder)
{
	if(!bIsValid) return;
	if(bOrder)
	{
		if(GetNextMusicModIndex() == 0) FindChannelOfMusic(true, false);
		MusicIndex = GetNextMusicModIndex();
	}else
	{
		if(GetLastMusicModIndex() == MusicFullName.Num() - 1) FindChannelOfMusic(false, false);
		MusicIndex = GetLastMusicModIndex();
	}
}

void AMainMusicRadio::ChangeChannel(bool bOrder)
{
	if(!bIsValid) return;
	FindChannelOfMusic(bOrder, true);
}

bool AMainMusicRadio::LoadChannels()
{
	IFileManager& FileManager = IFileManager::Get();
	FileManager.FindFiles(ChannelName, *(MusicFolderPath / "*"), false, true);
	MusicOfChannelCache.AddZeroed(ChannelName.Num());
	return !ChannelName.IsEmpty();
}

bool AMainMusicRadio::LoadMusicsFromChannel()
{
	IFileManager& FileManager = IFileManager::Get();
	MusicFullName.Empty();
	FileManager.FindFiles(MusicFullName, *(MusicFolderPath / ChannelName[ChannelIndex] / "*.wav"), true, false);
	return !MusicFullName.IsEmpty();
}