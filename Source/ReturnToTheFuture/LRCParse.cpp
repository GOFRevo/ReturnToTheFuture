#include "LRCParse.h"
#include "MusicRadioStruct.h"
#include "RTFUtility.h"

float FLRCParse::ParseTimeFromString(const FString& Text)
{
	const FString& Min = Text.Mid(0, 2);
	if(!FRTFUtility::IsDigit(Min[0]) || !FRTFUtility::IsDigit(Min[1])) return -1.0f;
	const FString& Sec = Text.Mid(3, 2);
	if(!FRTFUtility::IsDigit(Sec[0]) || !FRTFUtility::IsDigit(Sec[1])) return -1.0f;
	float Result = FCString::Atoi(*Min) * 60.0f + FCString::Atoi(*Sec);
	if(Text.Len() == 8)
	{
		const FString& Mm = Text.Right(2);
		if(!FRTFUtility::IsDigit(Mm[0]) || !FRTFUtility::IsDigit(Mm[1])) return -1.0f;
		Result += FCString::Atoi(*Mm) / 100.0f;
	}
	return Result;
}

TArray<FString> FLRCParse::ParseLyricFromString(const FString& Text)
{
	TArray<FString> Temp;
	Text.ParseIntoArray(Temp, TEXT("\n"), true);
	
	TArray<FString> Result;
	for(FString& T: Temp)
	{
		T.TrimStartAndEndInline();
		if(!T.IsEmpty()) Result.Add(T);
	}
	return Result;
}

FString FLRCParse::ParseMusicNameFromString(const FString& Text, int32& Index)
{
	const int32 StartIndex = Text.Find("[", ESearchCase::IgnoreCase, ESearchDir::FromStart, Index);
	Index = StartIndex;
	if(StartIndex == INDEX_NONE) return "";
	
	const int32 EndIndex = Text.Find("]", ESearchCase::IgnoreCase, ESearchDir::FromStart, Index);
	if(EndIndex == INDEX_NONE)
	{
		Index = INDEX_NONE;
		return "";
	}
	const int32 Interval = EndIndex - StartIndex - 1;
	if(Interval <= 3)
	{
		Index = EndIndex + 1;
		return "";
	}
	const FString& Element = Text.Mid(StartIndex + 1, Interval);
	if(!Element.StartsWith("ti:")) return "";
	Index = EndIndex + 1;
	return (Element.Right(Element.Len() - 3));
}

FString FLRCParse::ParseAuthorNameFromString(const FString& Text, int32& Index)
{
	const int32 StartIndex = Text.Find("[", ESearchCase::IgnoreCase, ESearchDir::FromStart, Index);
	Index = StartIndex;
	if(StartIndex == INDEX_NONE) return "None";
	
	const int32 EndIndex = Text.Find("]", ESearchCase::IgnoreCase, ESearchDir::FromStart, Index);
	if(EndIndex == INDEX_NONE)
	{
		Index = INDEX_NONE;
		return "None";
	}
	const int32 Interval = EndIndex - StartIndex - 1;
	if(Interval <= 3)
	{
		Index = EndIndex + 1;
		return "None";
	}
	const FString& Element = Text.Mid(StartIndex + 1, Interval);
	if(!Element.StartsWith("ar:")) return "None";
	Index = EndIndex + 1;
	return Element.Right(Element.Len() - 3);
}

UMusicTimeLine* FLRCParse::ParseMusicTimeLineFromString(const FString& Text, int32& Index)
{
	while(true)
	{
		const int32 StartIndex = Text.Find("[", ESearchCase::IgnoreCase, ESearchDir::FromStart, Index);
		Index = StartIndex;
		if(StartIndex == INDEX_NONE) return nullptr;
		
		const int32 EndIndex = Text.Find("]", ESearchCase::IgnoreCase, ESearchDir::FromStart, Index);
		if(EndIndex == INDEX_NONE)
		{
			Index = INDEX_NONE;
			return nullptr;
		}
		Index = EndIndex + 1;
		const int32 Interval = EndIndex - StartIndex - 1;
		if(Interval != 5 && Interval != 8) continue;
		
		const FString& Element = Text.Mid(StartIndex + 1, Interval);
		const float Time = ParseTimeFromString(Element);
		if(Time < 0.0f) continue;

		const int32 NewStartIndex = Index;
		int32 NewEndIndex = Text.Find("[", ESearchCase::IgnoreCase, ESearchDir::FromStart, Index);
		if(NewEndIndex == INDEX_NONE) NewEndIndex = Text.Len();
		Index = NewEndIndex;
		const int32 NewInterval = NewEndIndex - NewStartIndex;
		if(NewInterval <= 0) continue;
		const FString& NewElement = Text.Mid(NewStartIndex, NewInterval);
		TArray<FString> Lyric = ParseLyricFromString(NewElement);
		if(Lyric.IsEmpty()) continue;
		
		UMusicTimeLine* Result = NewObject<UMusicTimeLine>();
		check(Result != nullptr)
		Result->Time = Time;
		Result->Lyric = std::move(Lyric);
		return Result;
	}
}