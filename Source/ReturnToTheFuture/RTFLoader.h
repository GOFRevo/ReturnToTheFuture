#pragma once

#include "CoreMinimal.h"

class FRTFLoader
{
public:
	static USoundWave* LoadSoundWaveFromFile(const FString& FilePath);
};
