// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMusicRadio.h"
#include "Components/AudioComponent.h"
#include "RTFInfo.h"
#include "RTFLoader.h"

AMainMusicRadio::AMainMusicRadio():
	bGood(true),
	CurrentChannelIndex(0),
	CurrentSongIndex(0)
{
	MusicFolderPath = FRTFInfo::ResourcePath + "/Music/";
}

void AMainMusicRadio::BeginPlay()
{
	Super::BeginPlay();
	
	bGood = LoadChannels();
	if(!bGood) return;
	
	bGood = LoadSongFromChannel();
	if(!bGood) return;
	
	bGood = ChangeChannelImpl(true, false);
	if(!bGood) return;
	
	bGood = LoadSongData();
	Play(true);
}

void AMainMusicRadio::Tick(float DeltaTime)
{
	if(SongData.bIsOn) SongData.StartTime += DeltaTime;
}

void AMainMusicRadio::Init(bool bStart)
{
	// Super::Init(bStart);
}

void AMainMusicRadio::Start()
{
	// Super::Start();
}

void AMainMusicRadio::End()
{
	// Super::End();
}

void AMainMusicRadio::Play(bool bNew)
{
	// Super::Play();
	SongData.bIsOn = true;
	if(bNew)
	{
		// Audio->SetWaveParameter(TEXT("Music"), SongData.SoundWave);
		Debug = SongData.SoundWave;
		Audio->SetWaveParameter(TEXT("Music"), Debug);
		Audio->SetFloatParameter(TEXT("TotalTime"), SongData.TotalTime);
	}
	Audio->SetFloatParameter(TEXT("StartTime"), SongData.StartTime);
	Audio->Play();
}

void AMainMusicRadio::Stop()
{
	// Super::Stop();
}

void AMainMusicRadio::ChangeSongImpl(bool bNext)
{
	if(bNext)
	{
		if(ModNextSongIndex() == 0) ChangeChannelImpl(true, false);
		CurrentSongIndex = ModNextSongIndex();
	}else
	{
		if(ModLastSongIndex() == SongPath.Num() - 1) ChangeChannelImpl(false, false);
		CurrentSongIndex = ModLastSongIndex();
	}
}

bool AMainMusicRadio::ChangeChannelImpl(bool bNext, bool bChangeSongIndex){
	if(ChannelName.Num() == 1) return !SongPath.IsEmpty();
	const uint64_t Old = CurrentChannelIndex;
	while(true)
	{
		if(bNext) ModNextChannelIndex();
		else ModLastChannelIndex();
		
		if(LoadSongFromChannel())
		{
			if(bChangeSongIndex)
			{
				ChannelChangeIndex[Old] = CurrentSongIndex;
				CurrentSongIndex = ChannelChangeIndex[CurrentChannelIndex];
			}
			return true;
		}
		if(CurrentChannelIndex == Old) return false;
	}
}

uint64_t AMainMusicRadio::ModNextSongIndex() const
{
	return (CurrentSongIndex + 1) % SongPath.Num();
}

void AMainMusicRadio::ModNextChannelIndex()
{
	CurrentChannelIndex = (CurrentChannelIndex + 1) % ChannelName.Num();
}

uint64_t AMainMusicRadio::ModLastSongIndex() const
{
	if(CurrentChannelIndex == 0) return SongPath.Num() - 1;
	return CurrentSongIndex - 1;
}

void AMainMusicRadio::ModLastChannelIndex()
{
	CurrentChannelIndex = CurrentChannelIndex == 0? SongPath.Num() - 1: CurrentChannelIndex - 1;
}

void AMainMusicRadio::ChangeSong(bool bNext)
{
	if(!bGood) return;
	ChangeSongImpl(bNext);
}

void AMainMusicRadio::ChangeChannel(bool bNext)
{
	if(!bGood) return;
	ChangeChannelImpl(bNext, true);
}

bool AMainMusicRadio::LoadChannels()
{
	IFileManager& FileManager = IFileManager::Get();
	FileManager.FindFiles(ChannelName, *(MusicFolderPath + "*"), false, true);
	ChannelChangeIndex.AddZeroed(ChannelName.Num());
	return !ChannelName.IsEmpty();
}

bool AMainMusicRadio::LoadSongFromChannel()
{
	IFileManager& FileManager = IFileManager::Get();
	SongPath.Empty();
	FileManager.FindFiles(SongPath, *(MusicFolderPath + ChannelName[CurrentChannelIndex] + "/*.wav"), true, false);
	return !SongPath.IsEmpty();
}

bool AMainMusicRadio::LoadSongData()
{
	SongData.SoundWave = FRTFLoader::LoadSoundWaveFromFile(*(MusicFolderPath + ChannelName[CurrentChannelIndex] + "/" + SongPath[CurrentSongIndex]));
	if(SongData.SoundWave == nullptr) return false;
	SongData.bIsOn = false;
	SongData.StartTime = 0.0f;
	SongData.TotalTime = SongData.SoundWave->GetDuration();
	return true;
}
