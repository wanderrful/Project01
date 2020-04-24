// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "InteractionSubsystem.h"
#include "Engine/LocalPlayer.h"
#include "Engine.h"
#include "GameFramework/PlayerController.h"
#include "Project01/Project01.h"
#include "Project01/Interfaces/Interactable.h"

UInteractionSubsystem::UInteractionSubsystem()
{
	ULocalPlayer *p = this->GetLocalPlayer();
	UWorld *w = p ? p->GetWorld() : nullptr;
	if (w)
		this->_StartTimer();
}

void UInteractionSubsystem::_StartTimer()
{
	ULocalPlayer *p = this->GetLocalPlayer();
	UWorld *w = p ? p->GetWorld() : nullptr;

	check(w);

	w->GetGameInstance()->GetTimerManager().SetTimer(
		InteractionUpdateTimer,
		this,
		&UInteractionSubsystem::UpdateTarget,
		0.1f,
		true,
		1.f);
}

void UInteractionSubsystem::OnInteract()
{
	this->_OnInteract();
}

void UInteractionSubsystem::_OnInteract()
{
	ULocalPlayer *p = this->GetLocalPlayer();
	UWorld *w = p ? p->GetWorld() : nullptr;

	if (w)
	{
		if (this->Target)
		{
			TArray<UActorComponent *> interactableComponents = Target->GetComponentsByInterface(UInteractable::StaticClass());

			if (interactableComponents.Num() > 0)
			{

				for (auto &component : interactableComponents)
				{
					IInteractable *_component = Cast<IInteractable>(component);
					_component->Execute_OnInteract(component);
				}
			}
		}
	}
}

bool UInteractionSubsystem::SetTarget(AActor *target)
{
	Target = target ? target : nullptr;
	return (bool)target;
}

AActor *UInteractionSubsystem::GetTarget()
{
	return Target;
}

void UInteractionSubsystem::UpdateTarget()
{
	ULocalPlayer *lp = this->GetLocalPlayer();

	APlayerController *pc = lp->PlayerController;
	if (!pc)
		return;

	APawn *p = pc->GetPawn();
	if (!p)
		return;

	FHitResult hit;
	FCollisionQueryParams params;
	FVector start = p->GetActorLocation();
	FVector end = start + p->GetActorForwardVector() * this->GetInteractionDistance();
	end.Z = start.Z;
	params.AddIgnoredActor(p);

	if (p->GetWorld()->SweepSingleByChannel(
			hit,
			start,
			end,
			FQuat::Identity,
			ECC_Camera,
			FCollisionShape::MakeSphere(64.f),
			params))
	{
		AActor *a = hit.Actor.Get();

		TArray<UActorComponent *> interactableComponents = a->GetComponentsByInterface(UInteractable::StaticClass());
		if (interactableComponents.Num() > 0)
		{
			this->SetTarget(a);
			return;
		}
	}

	this->SetTarget(nullptr);
}