// Copyright Epic Games, Inc. All Rights Reserved.

#include "UTHUB_GASGameMode.h"
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