// Copyright Epic Games, Inc. All Rights Reserved.

#include "UTHUB_GASPlayerController.h"
#include "GameFramework/Pawn.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "UTHUB_GASCharacter.h"
#include "Engine/World.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "EnhancedInputSubsystems.h"
#include "DataDriven/GASDataComponent.h"
#include "DataDriven/InputAbilityMapping.h"
#include "Engine/LocalPlayer.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

AUTHUB_GASPlayerController::AUTHUB_GASPlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
	CachedDestination = FVector::ZeroVector;
	FollowTime = 0.f;
}

void AUTHUB_GASPlayerController::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();
}



void AUTHUB_GASPlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	// Add Input Mapping Context
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}

	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		// Setup mouse input events
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Started, this, &AUTHUB_GASPlayerController::OnInputStarted);
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Triggered, this, &AUTHUB_GASPlayerController::OnSetDestinationTriggered);
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Completed, this, &AUTHUB_GASPlayerController::OnSetDestinationReleased);
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Canceled, this, &AUTHUB_GASPlayerController::OnSetDestinationReleased);

		// Setup touch input events
		EnhancedInputComponent->BindAction(SetDestinationTouchAction, ETriggerEvent::Started, this, &AUTHUB_GASPlayerController::OnInputStarted);
		EnhancedInputComponent->BindAction(SetDestinationTouchAction, ETriggerEvent::Triggered, this, &AUTHUB_GASPlayerController::OnTouchTriggered);
		EnhancedInputComponent->BindAction(SetDestinationTouchAction, ETriggerEvent::Completed, this, &AUTHUB_GASPlayerController::OnTouchReleased);
		EnhancedInputComponent->BindAction(SetDestinationTouchAction, ETriggerEvent::Canceled, this, &AUTHUB_GASPlayerController::OnTouchReleased);
		
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}

	
}


void AUTHUB_GASPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
	UCustomAbilitySystemComponent* CASC = GetPawn()->FindComponentByClass<UCustomAbilitySystemComponent>();
	const UGASDataComponent* DataComponent = GetPawn()->FindComponentByClass<UGASDataComponent>();
	if (EnhancedInputComponent && CASC && DataComponent)
	{
		for (const TPair<UInputAction*, TSubclassOf<UGameplayAbility>>& PairMapping : DataComponent->InputAbilityMapping->InputMappings)
		{
			CASC->AddAbilityFromClass(PairMapping.Value);
			EnhancedInputComponent->BindAction(PairMapping.Key, ETriggerEvent::Started, this, &ThisClass::ExecuteAbility);
		}
	}
}

void AUTHUB_GASPlayerController::ExecuteAbility(const FInputActionInstance& Inst)
{
	const UGASDataComponent* DataComponent = GetPawn()->FindComponentByClass<UGASDataComponent>();

	UCustomAbilitySystemComponent* CASC = GetPawn()->FindComponentByClass<UCustomAbilitySystemComponent>();
	
	if (DataComponent && DataComponent->InputAbilityMapping && CASC)
	{
		CASC->TryActivateAbilityByClass(*DataComponent->InputAbilityMapping->InputMappings.Find(Inst.GetSourceAction()));
	}
}


void AUTHUB_GASPlayerController::OnInputStarted()
{
	StopMovement();
}

// Triggered every frame when the input is held down
void AUTHUB_GASPlayerController::OnSetDestinationTriggered()
{
	// We flag that the input is being pressed
	FollowTime += GetWorld()->GetDeltaSeconds();
	
	// We look for the location in the world where the player has pressed the input
	FHitResult Hit;
	bool bHitSuccessful = false;
	if (bIsTouch)
	{
		bHitSuccessful = GetHitResultUnderFinger(ETouchIndex::Touch1, ECollisionChannel::ECC_Visibility, true, Hit);
	}
	else
	{
		bHitSuccessful = GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, Hit);
	}

	// If we hit a surface, cache the location
	if (bHitSuccessful)
	{
		CachedDestination = Hit.Location;
	}
	
	// Move towards mouse pointer or touch
	APawn* ControlledPawn = GetPawn();
	if (ControlledPawn != nullptr)
	{
		FVector WorldDirection = (CachedDestination - ControlledPawn->GetActorLocation()).GetSafeNormal();
		ControlledPawn->AddMovementInput(WorldDirection, 1.0, false);
	}
}

void AUTHUB_GASPlayerController::OnSetDestinationReleased()
{
	// If it was a short press
	if (FollowTime <= ShortPressThreshold)
	{
		// We move there and spawn some particles
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, CachedDestination);
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, FXCursor, CachedDestination, FRotator::ZeroRotator, FVector(1.f, 1.f, 1.f), true, true, ENCPoolMethod::None, true);
	}

	FollowTime = 0.f;
}

// Triggered every frame when the input is held down
void AUTHUB_GASPlayerController::OnTouchTriggered()
{
	bIsTouch = true;
	OnSetDestinationTriggered();
}

void AUTHUB_GASPlayerController::OnTouchReleased()
{
	bIsTouch = false;
	OnSetDestinationReleased();
}

void AUTHUB_GASPlayerController::PerformFirstAbility()
{

	// APawn* ControlledPawn = GetPawn();
	// if (ControlledPawn)
	// {
	// 	if (AUTHUB_GASCharacter* Character = Cast<AUTHUB_GASCharacter>(ControlledPawn))
	// 	{
	// 		Character->PerformFirstAttack();
	// 	}
	// }
	
}


