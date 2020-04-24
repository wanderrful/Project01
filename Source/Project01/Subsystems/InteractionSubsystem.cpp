// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "InteractionSubsystem.h"
#include "Engine/LocalPlayer.h"
#include "Engine.h"
#include "GameFramework/PlayerController.h"
#include "Project01/Project01.h"
#include "Project01/Interfaces/Interactable.h"

UInteractionSubsystem::UInteractionSubsystem()
{
	UE_LOG(LogProject01, Warning, TEXT("UInteractionSubsystem Hello"))
}

void UInteractionSubsystem::OnInteract()
{
	TryInteract();
}

void UInteractionSubsystem::TryInteract()
{
	ULocalPlayer *p = GetLocalPlayer();
	UWorld *w = p ? p->GetWorld() : nullptr;

	if (w)
	{
		TArray<FStringFormatArg> Args;
		Args.Add(Target ? TEXT("Yes!") : TEXT("None"));
		GEngine->AddOnScreenDebugMessage(INDEX_NONE, 5.f, FColor::Green, FString::Format(TEXT("actor={0}"), Args));

		Target->OnInteract();
	}
}

bool UInteractionSubsystem::SetTarget(IInteractable *target)
{
	Target = target ? target : nullptr;
	return (bool)target;
}