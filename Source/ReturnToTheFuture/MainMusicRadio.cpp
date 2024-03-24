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
	if(IsPlaying() && IsValid()) StartTime += DeltaTime;
}

void UMusicData::Play(){
	if(IsPlaying()) return;
	while(!IsValid()) std::this_thread::yield();
	AudioComp->SetFloatParameter(TEXT("StartTime"), StartTime);
	AudioComp->SetWaveParameter(TEXT("Music"), SoundWave);
	AudioComp->Play();
	bIsPlaying = true;
}

void UMusicData::Stop()
{
	if(!IsPlaying() || !IsValid()) return;
	bIsPlaying = false;
	AudioComp->Stop();
}

void UMusicData::ClearState()
{
	StartTime = 0.0f;
}

void UMusicData::ClearResource()
{
	bIsValid = false;
	ClearState();
	bAutoStart = false;
	bIsPlaying = false;
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
	if(!IsValid()) return;
	MusicData->Play();
}

void AMainMusicRadio::Stop()
{
	if(!IsValid()) return;
	MusicData->Stop();
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

void AMainMusicRadio::ChangeMusic(bool bOrder)
{
	if(!IsValid()) return;
	const bool bAutoStart = PreLoadNewMusic();
	
	if(bOrder)
	{
		MusicIndex = GetNextMusicModIndex();
		if(MusicIndex == 0)
		{
			MusicOfChannelCache[ChannelIndex] = 0;
			FindChannelOfMusic(true, false);
		}
	}else
	{
		if(MusicIndex == 0)
		{
			MusicOfChannelCache[ChannelIndex] = 0;
			FindChannelOfMusic(false, false);
		}
		MusicIndex = GetLastMusicModIndex();
	}

	PostLoadNewMusic(bAutoStart);
}

void AMainMusicRadio::ChangeChannel(bool bOrder)
{
	if(!IsValid()) return;
	const bool bAutoStart = PreLoadNewMusic();
	FindChannelOfMusic(bOrder, true);
	PostLoadNewMusic(bAutoStart);
}

bool AMainMusicRadio::PreLoadNewMusic()
{
	const bool bNewAutoStart = MusicData->IsPlaying();
	Stop();
	MusicData->ClearResource();
	return bNewAutoStart;
}

void AMainMusicRadio::PostLoadNewMusic(bool bAutoStart)
{
	const FString MusicPath = MusicFolderPath / ChannelName[ChannelIndex] / MusicFullName[MusicIndex];
	MusicData->LoadMusic(MusicPath, bAutoStart);
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