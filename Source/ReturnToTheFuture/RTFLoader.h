#pragma once

#include "CoreMinimal.h"

class UMusicLRC;
class FRTFLoader
{
public:
	static USoundWave* LoadSoundWaveFromFile(const FString& FilePath);
	static UMusicLRC* LoadMusicLRCFromFile(const FString& FilePath);
};
