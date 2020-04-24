// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "Project01GameMode.h"
#include "Project01PlayerController.h"
#include "Project01PlayerState.h"
#include "Project01Character.h"
#include "Project01GameState.h"
#include "Project01Character.h"
#include "Project01/HUDs/Project01HUD.h"
#include "UObject/ConstructorHelpers.h"

AProject01GameMode::AProject01GameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = AProject01PlayerController::StaticClass();
	DefaultPawnClass = AProject01Character::StaticClass();
	PlayerStateClass = AProject01PlayerState::StaticClass();
	GameStateClass = AProject01GameState::StaticClass();
	HUDClass = AProject01HUD::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDownCPP/Blueprints/TopDownCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}