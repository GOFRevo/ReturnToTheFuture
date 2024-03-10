// Fill out your copyright notice in the Description page of Project Settings.


#include "RTFCameraAnimInstance.h"
#include "RTFCameraManager.h"

URTFCameraAnimInstance::URTFCameraAnimInstance():
	CameraViewState(ECameraViewState::ECVS_EmptyView),
	bIFToITHasCompelete(false),
	bITToIFHasCompelete(false)
{
	
}

void URTFCameraAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
}

void URTFCameraAnimInstance::UpdateEssentialInfo()
{
	CameraViewState = ARTFCameraManager::GetInstance()->CameraViewState;
}

void URTFCameraAnimInstance::UpdateSpaceShipInfo()
{
	UpdateEssentialInfo();
	UpdateSpaceShipCachedInfo();
}

void URTFCameraAnimInstance::UpdateSpaceShipCachedInfo()
{
	
}

void URTFCameraAnimInstance::UpdateITInfo()
{
	UpdateEssentialInfo();
	
}

void URTFCameraAnimInstance::UpdateIFInfo()
{
	UpdateEssentialInfo();
	
}

void URTFCameraAnimInstance::UpdateOTInfo()
{
	UpdateEssentialInfo();
	
}

void URTFCameraAnimInstance::ClearIFCompeleteFlag()
{
	bITToIFHasCompelete = false;
}

void URTFCameraAnimInstance::ClearITCompeleteFlag()
{
	bIFToITHasCompelete = false;
}
