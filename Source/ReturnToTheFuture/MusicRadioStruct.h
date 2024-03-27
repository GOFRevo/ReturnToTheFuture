#pragma once
#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "MusicRadioEnums.h"
#include "MusicRadioStruct.generated.h"

USTRUCT(BlueprintType)
struct FMusicRadioInfo: public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bIsOpened = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	EMusicRadioState MusicRadioState = EMusicRadioState::EMRS_Invalid;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FText ChannelName;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FText MusicName;
};

UCLASS()
class UMusicLRC: public UObject 
{
	GENERATED_BODY()
public:
	int32 Index = 0;
	FString MusicName;
	FString AuthorName;
	FString Lyric;
};

UCLASS(BlueprintType)
class UMusicTimeLine: public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float Time = 0.0f;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<FString> Lyric;
};