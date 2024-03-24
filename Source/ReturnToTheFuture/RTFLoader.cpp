#include "RTFLoader.h"
#include "RTFMacro.h"
#include "Sound/SoundWaveProcedural.h"

#ifdef RTF_DEBUG
void DebugInfoOfSoundWave(USoundWave* SoundWave)
{
	if(SoundWave == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("SoundWave: SoundWave Pointer Is Null!"))
		return;
	}
	UE_LOG(LogTemp, Warning, TEXT("SoundWave: Duration - %f"), SoundWave->GetDuration());
	UE_LOG(LogTemp, Warning, TEXT("SoundWave: Channel Num - %d"), SoundWave->NumChannels);
	UE_LOG(LogTemp, Warning, TEXT("SoundWave: RawPCMDataSize - %d"), SoundWave->RawPCMDataSize);
}
#endif

USoundWave* FRTFLoader::LoadSoundWaveFromFile(const FString& FilePath){
	/*
	USoundWaveProcedural* NewSoundWave = NewObject<USoundWaveProcedural>();
	if (NewSoundWave == nullptr) return nullptr;
	
	TArray <uint8> RawData;
	if(!FFileHelper::LoadFileToArray(RawData, FilePath.GetCharArray().GetData())) return nullptr;
	
	FWaveModInfo WaveInfo;
	if (!WaveInfo.ReadWaveInfo(RawData.GetData(), RawData.Num())) return nullptr;

	NewSoundWave->QueueAudio(WaveInfo.SampleDataStart, WaveInfo.SampleDataSize);
	NewSoundWave->Duration = *WaveInfo.pWaveDataSize * 8.0f / (*WaveInfo.pChannels * *WaveInfo.pBitsPerSample * *WaveInfo.pSamplesPerSec);
	NewSoundWave->SetSampleRate(*WaveInfo.pSamplesPerSec);
	NewSoundWave->NumChannels = *WaveInfo.pChannels;
	NewSoundWave->DecompressionType = DTYPE_Procedural;
	NewSoundWave->TotalSamples = *WaveInfo.pSamplesPerSec * NewSoundWave->Duration;
	NewSoundWave->SetSoundAssetCompressionType(ESoundAssetCompressionType::PCM);
	NewSoundWave->PostImport();
	return NewSoundWave;
	*/
	return nullptr;

	
}