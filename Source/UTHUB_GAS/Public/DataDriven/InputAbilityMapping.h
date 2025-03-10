
#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "Engine/DataAsset.h"
#include "Abilities/GameplayAbility.h"
#include "InputAbilityMapping.generated.h"


class UInputAction;

UCLASS()
class UTHUB_GAS_API UInputAbilityMapping : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category="Mappings")
	TMap<UInputAction*, TSubclassOf<UGameplayAbility>> InputMappings;
};
