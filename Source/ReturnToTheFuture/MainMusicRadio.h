// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MainRadio.h"
#include "MusicRadioEnums.h"
#include "MusicRadioStruct.h"
#include "MainMusicRadio.generated.h"
/**
 * 
 */
class UMusicData;
class UWidgetComponent;
UCLASS()
class RETURNTOTHEFUTURE_API AMainMusicRadio : public AMainRadio
{
	GENERATED_BODY()
private:
	bool bIsOpened;
	EMusicRadioState MusicRadioState;
	FString MusicFolderPath;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MusicRadioInfo", Meta = (AllowPrivateAccess = "true"))
	FText ChannelNameText;
	TArray<FString> ChannelName;
	TArray<uint64_t> MusicOfChannelCache;
	uint64_t ChannelIndex;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MusicRadioInfo", Meta = (AllowPrivateAccess = "true"))
	FText MusicNameText;
	TArray<FString> MusicName;
	uint64_t MusicIndex;
	
	UPROPERTY()
	UMusicData* MusicData;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MusicRadioInfo", Meta = (AllowpRivateAccess = "true"))
	FMusicRadioInfo MusicRadioInfo;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget", Meta = (AllowPrivateAccess = "true"))
	UWidgetComponent* RadioWidget;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Submix", Meta = (AllowPrivateAccess = "true"))
	USoundSubmix* Submix;
public:
	AMainMusicRadio();

	void BeginPlay() override;
	void Tick(float DeltaTime) override;

	void UpdataSubmix();
	void UpdateMusicRadioState(UMusicData* MD);

	void Init(bool bAutoStart) override;
	void OpenDevice() override;
	void CloseDevice() override;
	
	void Play() override;
	void Pause() override;
	
	bool FindChannelOfMusic(bool bOrder, bool bChangeSongIndex);
	uint64_t GetNextMusicModIndex() const;
	uint64_t GetLastMusicModIndex() const;
	void ModNextChannelModIndex();
	void ModLastChannelModIndex();
	
	void ChangeMusic(bool bOrder);
	void ChangeChannel(bool bOrder);
	void LoadNewMusic(bool bAutoStart);
	void AutoNext();
	void RefreshMusicRadioInfo();
	void ChangeChannelNameText();
	void ChangeMusicNameText();
	
	bool LoadChannels();
	bool LoadMusicsFromChannel();
	
	bool IsValid() const{ return MusicRadioState != EMusicRadioState::EMRS_Invalid; }
	virtual bool IsOpened() override;
	virtual bool IsPlaying() override;
	bool IsPaused();
	EMusicRadioState GetMusicRadioState() const;
	UFUNCTION(BlueprintCallable)
	const FMusicRadioInfo& GetMusicRadioInfo() const;
	FText GetChannleNameText() const;
	FText GetMusicNameText() const;
	UFUNCTION(BlueprintCallable)
	UMusicTimeLine* GetMusicTimeLine();
	UFUNCTION(BlueprintCallable)
	bool IsFirstTimeLine() const;
	UFUNCTION(BlueprintCallable)
	bool CanGetMusicTimeLine() const;
	UFUNCTION(BlueprintCallable)
	float GetMusicStartTime() const;
};
