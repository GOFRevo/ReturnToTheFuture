// Fill out your copyright notice in the Description page of Project Settings.


#include "RTFCameraAnimInstance.h"
#include "RTFCameraManager.h"

URTFCameraAnimInstance::URTFCameraAnimInstance():
	CameraViewState(ECameraViewState::ECVS_EmptyView)
{
	
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
