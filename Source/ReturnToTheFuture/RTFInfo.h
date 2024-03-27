#pragma once

#include "CoreMinimal.h"


struct FRTFInfo
{
	inline static FString ResourcePath = FPaths::ProjectModsDir();
	inline static FString EmptyString = "";
	inline static FText InvalidText = FText::FromString(TEXT("Invalid"));
};
