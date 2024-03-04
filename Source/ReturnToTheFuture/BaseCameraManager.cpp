// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCameraManager.h"

ABaseCameraManager::ABaseCameraManager():
	CameraFOV(90.0f)
{
	
}

bool ABaseCameraManager::CustomCamera(float DeltaTime, FMinimalViewInfo& ViewInfo)
{
	return false;
}

