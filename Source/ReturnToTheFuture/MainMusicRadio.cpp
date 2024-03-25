// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMusicRadio.h"
#include "RTFInfo.h"
#include "MusicData.h"
#include "Components/WidgetComponent.h"

AMainMusicRadio::AMainMusicRadio():
	bIsOpened(true),
	MusicRadioState(EMusicRadioState::EMRS_Invalid),
	ChannelIndex(0),
	MusicIndex(0),
	MusicData(nullptr)
{
	MusicFolderPath = FRTFInfo::ResourcePath / "Music";
	
	RadioWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("RadioWidgetComponent"));
	RadioWidget->SetupAttachment(GetRootComponent());
}

void AMainMusicRadio::BeginPlay()
{
	Super::BeginPlay();
	
	if(!LoadChannels() || !LoadMusicsFromChannel() || !FindChannelOfMusic(true, false)) return;
	
	MusicData = UMusicData::CreateMusicData(Audio);
	LoadNewMusic(true);
}

void AMainMusicRadio::Tick(float DeltaTime)
{
	if(IsOpened())
	{
		MusicData->MusicTick(DeltaTime);
		if(MusicData->HasPlayComplete()) AutoNext();
	}
	UpdateMusicRadioState(MusicData);
}

void AMainMusicRadio::UpdateMusicRadioState(UMusicData* MD)
{
	switch(MD->GetMusicDataState()){
	case EMusicDataState::EMDS_Playing:
	case EMusicDataState::EMDS_Stopped:
	case EMusicDataState::EMDS_PlayComplete:
		MusicRadioState = EMusicRadioState::EMRS_Playing;
		break;
	case EMusicDataState::EMDS_Paused:
	case EMusicDataState::EMDS_LoadComplete:
		MusicRadioState = EMusicRadioState::EMRS_Paused;
		break;
	case EMusicDataState::EMDS_Loading:
		MusicRadioState = EMusicRadioState::EMRS_Loading;
	default:
		UE_LOG(LogTemp, Warning, TEXT("MusicDataState: InValid"))
	}
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
	if(MusicData->HasLoadComplete()) MusicData->Play();
	else MusicData->Pause(false);
}

void AMainMusicRadio::Pause()
{
	if(!IsValid()) return;
	MusicData->Pause(true);
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
	
	const bool bNewAutoStart = MusicData->IsPlaying();
	MusicData->Stop();
	LoadNewMusic(bNewAutoStart);
}

void AMainMusicRadio::ChangeChannel(bool bOrder)
{
	if(!IsValid()) return;
	FindChannelOfMusic(bOrder, true);
	
	const bool bNewAutoStart = MusicData->IsPlaying();
	MusicData->Stop();
	LoadNewMusic(bNewAutoStart);
}

void AMainMusicRadio::LoadNewMusic(bool bAutoStart)
{
	const FString MusicPath = MusicFolderPath / ChannelName[ChannelIndex] / MusicFullName[MusicIndex];
	MusicData->LoadMusic(MusicPath, bAutoStart);
}

void AMainMusicRadio::AutoNext()
{
	MusicData->Stop();
	MusicIndex = GetNextMusicModIndex();
	if(MusicIndex == 0)
	{
		MusicOfChannelCache[ChannelIndex] = 0;
		FindChannelOfMusic(true, false);
	}
	LoadNewMusic(true);
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

bool AMainMusicRadio::IsOpened()
{
	return bIsOpened;
}

bool AMainMusicRadio::IsPlaying()
{
	return MusicRadioState == EMusicRadioState::EMRS_Playing;
}

bool AMainMusicRadio::IsPaused()
{
	return MusicRadioState == EMusicRadioState::EMRS_Paused;
}

EMusicRadioState AMainMusicRadio::GetMusicRadioState() const
{
	return MusicRadioState;
}

FMusicRadioInfo AMainMusicRadio::GetMusicRadioInfo() const
{
	FMusicRadioInfo Result;
	Result.bIsOpened = bIsOpened;
	Result.MusicRadioState = GetMusicRadioState();
	Result.MusicDataState = MusicData->GetMusicDataState();
	Result.ChannelName = IsValid()? ChannelName[ChannelIndex]: "Load Fail!";
	Result.MusicName = IsValid()? MusicFullName[MusicIndex]: "Load Fail!";
	return std::move(Result);
	
}