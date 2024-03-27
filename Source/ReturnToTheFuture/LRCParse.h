#pragma once
#include "CoreMinimal.h"

class UMusicTimeLine;
class FLRCParse
{
private:
	static float ParseTimeFromString(const FString& Text);
	static TArray<FString> ParseLyricFromString(const FString& Text);
public:
	static FString ParseMusicNameFromString(const FString& Text, int32& Index);
	static FString ParseAuthorNameFromString(const FString& Text, int32& Index);
	static UMusicTimeLine* ParseMusicTimeLineFromString(const FString& Text, int32& Index);
};
