// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/LocalPlayerSubsystem.h"
#include "InteractionSubsystem.generated.h"

class IInteractable;

UCLASS()
class UInteractionSubsystem : public ULocalPlayerSubsystem
{
	GENERATED_BODY()

public:
	UInteractionSubsystem();

	void OnInteract();
	bool SetTarget(IInteractable *target);

private:
	void TryInteract();

public:
	FORCEINLINE static float GetInteractionDistance() { return 500.f; }

private:
	UWorld *World;

	/* The Actor we will attempt to interact with */
	IInteractable *Target;
};
