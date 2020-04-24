// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "Project01PlayerController.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Runtime/Engine/Classes/Components/DecalComponent.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Project01Character.h"
#include "Engine/Engine.h"
#include "Engine/World.h"
#include "Engine/LocalPlayer.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Project01/Interaction/Subsystems/InteractionSubsystem.h"
#include "Project01/Interaction/Interfaces/Interactable.h"
#include "Project01/Project01.h"
#include "GameFramework/Actor.h"

AProject01PlayerController::AProject01PlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;
}

void AProject01PlayerController::BeginPlay()
{
}

void AProject01PlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	// keep updating the destination every tick while desired
	if (bMoveToMouseCursor)
	{
		MoveToMouseCursor();
	}
}

void AProject01PlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	InputComponent->BindAction("SetDestination", IE_Pressed, this, &AProject01PlayerController::OnSetDestinationPressed);
	InputComponent->BindAction("SetDestination", IE_Released, this, &AProject01PlayerController::OnSetDestinationReleased);

	// support touch devices
	InputComponent->BindTouch(EInputEvent::IE_Pressed, this, &AProject01PlayerController::MoveToTouchLocation);
	InputComponent->BindTouch(EInputEvent::IE_Repeat, this, &AProject01PlayerController::MoveToTouchLocation);

	InputComponent->BindAction("ResetVR", IE_Pressed, this, &AProject01PlayerController::OnResetVR);

	/* Connect player input to the Interaction Subsystem */
	UInteractionSubsystem *interactionSubsystem = GetInteractionSubsystem();
	if (interactionSubsystem)
	{
		InputComponent->BindAction(FName(TEXT("Interact")), IE_Pressed, interactionSubsystem, &UInteractionSubsystem::OnInteract);
	}
}

void AProject01PlayerController::OnResetVR()
{
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

void AProject01PlayerController::MoveToMouseCursor()
{
	if (UHeadMountedDisplayFunctionLibrary::IsHeadMountedDisplayEnabled())
	{
		if (AProject01Character *MyPawn = Cast<AProject01Character>(GetPawn()))
		{
			if (MyPawn->GetCursorToWorld())
			{
				UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, MyPawn->GetCursorToWorld()->GetComponentLocation());
			}
		}
	}
	else
	{
		// Trace to see what is under the mouse cursor
		FHitResult Hit;
		GetHitResultUnderCursor(ECC_Visibility, false, Hit);

		if (Hit.bBlockingHit)
		{
			// We hit something, move there
			SetNewMoveDestination(Hit.ImpactPoint);
		}
	}
}

void AProject01PlayerController::MoveToTouchLocation(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	FVector2D ScreenSpaceLocation(Location);

	// Trace to see what is under the touch location
	FHitResult HitResult;
	GetHitResultAtScreenPosition(ScreenSpaceLocation, CurrentClickTraceChannel, true, HitResult);
	if (HitResult.bBlockingHit)
	{
		// We hit something, move there
		SetNewMoveDestination(HitResult.ImpactPoint);
	}
}

void AProject01PlayerController::SetNewMoveDestination(const FVector DestLocation)
{
	APawn *const MyPawn = GetPawn();
	if (MyPawn)
	{
		float const Distance = FVector::Dist(DestLocation, MyPawn->GetActorLocation());

		// We need to issue move command only if far enough in order for walk animation to play correctly
		if ((Distance > 120.0f))
		{
			UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, DestLocation);
		}
	}
}

void AProject01PlayerController::OnSetDestinationPressed()
{
	// set flag to keep updating destination until released
	bMoveToMouseCursor = true;
}

void AProject01PlayerController::OnSetDestinationReleased()
{
	// clear flag to indicate we should stop updating the destination
	bMoveToMouseCursor = false;
}

UInteractionSubsystem *AProject01PlayerController::GetInteractionSubsystem()
{
	ULocalPlayer *p = Cast<ULocalPlayer>(this->Player);
	if (!p)
		return nullptr;

	UInteractionSubsystem *interactionSubsystem = p->GetSubsystem<UInteractionSubsystem>();
	if (!interactionSubsystem)
		return nullptr;

	return interactionSubsystem;
}