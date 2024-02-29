// Copyright Epic Games, Inc. All Rights Reserved.

#include "ReturnToTheFutureGameMode.h"
#include "ReturnToTheFutureCharacter.h"
#include "UObject/ConstructorHelpers.h"

AReturnToTheFutureGameMode::AReturnToTheFutureGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
