// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMusicRadio.h"
#include "RTFInfo.h"
#include "MusicData.h"

AMainMusicRadio::AMainMusicRadio():
	bIsOpened(true),
	MusicRadioState(EMusicRadioState::EMRS_Invalid),
	ChannelIndex(0),
	MusicIndex(0),
	MusicData(nullptr)
{
	MusicFolderPath = FRTFInfo::ResourcePath / "Music";
}

void AMainMusicRadio::BeginPlay()
{
	Super::BeginPlay();
	
	if(!LoadChannels() || !LoadMusicsFromChannel() || !FindChannelOfMusic(true, false)) return;
	
	MusicData = UMusicData::CreateMusicData(Audio);
	
	MusicData->SetValid(true);
	PostLoadNewMusic(true);
}

void AMainMusicRadio::Tick(float DeltaTime)
{
	MusicData->MusicTick(DeltaTime);
	if(MusicData->HasComplete()) AutoNext();
	UpdateMusicRadioState(MusicData);
}

void AMainMusicRadio::UpdateMusicRadioState(UMusicData* MD)
{
	const EMusicDataState MusicDataState = MD->GetMusicDataState();
	switch(MusicDataState){
	case EMusicDataState::EMDS_IsPlaying:
		MusicRadioState = EMusicRadioState::EMRS_Playing;
		break;
	case EMusicDataState::EMDS_IsStopping:
		MusicRadioState = EMusicRadioState::EMRS_Stopping;
		break;
	default:
		MusicRadioState = EMusicRadioState::EMRS_Loading;
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
	if(!IsValid() || !CanPlay()) return;
	MusicData->Play();
}

void AMainMusicRadio::Stop()
{
	if(!IsValid() || !CanStop()) return;
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

	MusicData->SetValid(true);
	PostLoadNewMusic(bAutoStart);
}

void AMainMusicRadio::ChangeChannel(bool bOrder)
{
	if(!IsValid()) return;
	const bool bAutoStart = PreLoadNewMusic();
	FindChannelOfMusic(bOrder, true);
	MusicData->SetValid(true);
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

void AMainMusicRadio::AutoNext()
{
	MusicData->Stop();
	MusicData->ClearResource();
	MusicIndex = GetNextMusicModIndex();
	if(MusicIndex == 0)
	{
		MusicOfChannelCache[ChannelIndex] = 0;
		FindChannelOfMusic(true, false);
	}
	MusicData->SetValid(true);
	PostLoadNewMusic(true);
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

bool AMainMusicRadio::IsPlaying()
{
	return MusicData->IsPlaying();
}

bool AMainMusicRadio::IsOpened()
{
	return bIsOpened;
}

EMusicRadioState AMainMusicRadio::GetMusicRadioState() const
{
	return MusicRadioState;
}

bool AMainMusicRadio::CanStop() const
{
	return MusicRadioState == EMusicRadioState::EMRS_Playing;
}

bool AMainMusicRadio::CanPlay() const
{
	return MusicRadioState == EMusicRadioState::EMRS_Stopping;
}

FMusicRadioInfo AMainMusicRadio::GetMusicRadioInfo() const
{
	FMusicRadioInfo Result;
	Result.bIsOpened = bIsOpened;
	Result.MusicRadioState = GetMusicRadioState();
	Result.ChannelName = IsValid()? ChannelName[ChannelIndex]: "Load Fail!";
	Result.MusicName = IsValid()? MusicFullName[MusicIndex]: "Load Fail!";
	return std::move(Result);
	
}