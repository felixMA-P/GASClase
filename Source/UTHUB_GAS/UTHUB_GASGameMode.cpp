// Copyright Epic Games, Inc. All Rights Reserved.

#include "UTHUB_GASGameMode.h"

#include "GameplayStatesManager.h"
#include "UTHUB_GASPlayerController.h"
#include "UTHUB_GASCharacter.h"
#include "UObject/ConstructorHelpers.h"

AUTHUB_GASGameMode::AUTHUB_GASGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = AUTHUB_GASPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDown/Blueprints/BP_TopDownCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	// set default controller to our Blueprinted controller
	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerBPClass(TEXT("/Game/TopDown/Blueprints/BP_TopDownPlayerController"));
	if(PlayerControllerBPClass.Class != NULL)
	{
		PlayerControllerClass = PlayerControllerBPClass.Class;
	}
}

void AUTHUB_GASGameMode::CharacterIsAllowedToInteract(FGameplayTag GameplayTag, int I)
{
}

void AUTHUB_GASGameMode::HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer)
{
	Super::HandleStartingNewPlayer_Implementation(NewPlayer);
	APawn* Pawn = NewPlayer->GetPawn();
	ensureMsgf(Pawn, TEXT("%s We dont have a proper pawn initialized yet"), ANSI_TO_TCHAR(__FUNCTION__));
	
	UCustomAbilitySystemComponent* ASC = Pawn->FindComponentByClass<UCustomAbilitySystemComponent>();
	if (ASC)
	{
		auto & Delegate = ASC->RegisterGameplayTagEvent(FGameplayStatesManager::Get().Tag_InteractEnable);
		Delegate.AddUObject(this, &ThisClass::CharacterIsAllowedToInteract);
	}
	
	
	
}
