// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMusicRadio.h"

#include "RTFInfo.h"
#include "MusicData.h"
#include "Components/AudioComponent.h"
#include "Components/WidgetComponent.h"
#include "Sound/SoundSubmix.h"

AMainMusicRadio::AMainMusicRadio():
	bIsOpened(true),
	MusicRadioState(EMusicRadioState::EMRS_Invalid),
	ChannelIndex(0),
	MusicIndex(0),
	MusicData(nullptr),
	Submix(nullptr)
{
	MusicFolderPath = FRTFInfo::ResourcePath / "Music";
	ChannelNameText = FRTFInfo::InvalidText;
	MusicNameText = FRTFInfo::InvalidText;
	
	RadioWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("RadioWidgetComponent"));
	RadioWidget->SetupAttachment(GetRootComponent());
}

void AMainMusicRadio::BeginPlay()
{
	Super::BeginPlay();
	
	if(!LoadChannels() || !LoadMusicsFromChannel() || !FindChannelOfMusic(true, false)) return;
	MusicRadioState = EMusicRadioState::EMRS_Valid;

	MusicData = UMusicData::CreateMusicData(Audio);

	LoadNewMusic(true);
}

void AMainMusicRadio::Tick(float DeltaTime)
{
	if(IsOpened())
	{
		UpdataSubmix();
		MusicData->MusicTick(DeltaTime);
		if(MusicData->HasPlayComplete()) AutoNext();
	}
	UpdateMusicRadioState(MusicData);
	RefreshMusicRadioInfo();
}

void AMainMusicRadio::UpdataSubmix()
{
	Audio->SetSubmixSend(Submix, 0.5f);
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
		MusicRadioState = EMusicRadioState::EMRS_Invalid;
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
	if(ChannelName.Num() == 1) return !MusicName.IsEmpty();
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
	return (MusicIndex + 1) % MusicName.Num();
}

uint64_t AMainMusicRadio::GetLastMusicModIndex() const
{
	return MusicIndex == 0? MusicName.Num() - 1: MusicIndex - 1;
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
	const FString MusicPath = MusicFolderPath / ChannelName[ChannelIndex] / MusicName[MusicIndex];
	MusicData->LoadMusic(MusicPath, bAutoStart);
	ChangeChannelNameText();
	ChangeMusicNameText();
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

void AMainMusicRadio::RefreshMusicRadioInfo()
{
	MusicRadioInfo.bIsOpened = bIsOpened;
	MusicRadioInfo.MusicRadioState = GetMusicRadioState();
	MusicRadioInfo.ChannelName = GetChannleNameText();
	MusicRadioInfo.MusicName = GetMusicNameText();
}

void AMainMusicRadio::ChangeChannelNameText()
{
	ChannelNameText = IsValid()? FText::FromString(ChannelName[ChannelIndex]): FRTFInfo::InvalidText;
}

void AMainMusicRadio::ChangeMusicNameText()
{
	if(!IsValid())
	{
		MusicNameText = FRTFInfo::InvalidText;
		return;
	}
	const FString& Result = MusicData->GetMusicName();
	MusicNameText = FText::FromString(Result.IsEmpty()? MusicName[MusicIndex]: Result);
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
	MusicName.Empty();
	FileManager.FindFiles(MusicName, *(MusicFolderPath / ChannelName[ChannelIndex] / "*.wav"), true, false);
	for(FString& MusicFullName: MusicName) check(MusicFullName.RemoveFromEnd(".wav"))
	return !MusicName.IsEmpty();
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

const FMusicRadioInfo& AMainMusicRadio::GetMusicRadioInfo() const
{
	return MusicRadioInfo;
}

FText AMainMusicRadio::GetChannleNameText() const
{
	return ChannelNameText;
}

FText AMainMusicRadio::GetMusicNameText() const
{
	return MusicNameText;
}

UMusicTimeLine* AMainMusicRadio::GetMusicTimeLine()
{
	return MusicData->GetMusicTimeLine();
}

bool AMainMusicRadio::IsFirstTimeLine() const
{
	return MusicData->IsFirstTimeLine();
}

bool AMainMusicRadio::CanGetMusicTimeLine() const
{
	return MusicData->CanGetMusicTimeLine();
}

float AMainMusicRadio::GetMusicStartTime() const
{
	return MusicData->GetMusicStartTime();
}

