// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GameFramework/GameModeBase.h"
#include "UTHUB_GASGameMode.generated.h"

UCLASS(minimalapi)
class AUTHUB_GASGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AUTHUB_GASGameMode();

	void CharacterIsAllowedToInteract(FGameplayTag GameplayTag, int I);
	virtual void HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer) override;

private:
	TArray<class UGameStates*> GameStateses;
};



