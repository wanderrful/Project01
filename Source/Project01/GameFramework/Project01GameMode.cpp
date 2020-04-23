// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "Project01GameMode.h"
#include "Project01PlayerController.h"
#include "Project01Character.h"
#include "UObject/ConstructorHelpers.h"

AProject01GameMode::AProject01GameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = AProject01PlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDownCPP/Blueprints/TopDownCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}