
#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "GameplayBaseStateTags.generated.h"

UCLASS()
class UTHUB_GAS_API UGameplayBaseStateTags : public UDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly) FGameplayTag Tag_Alive;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) FGameplayTag Tag_Dead;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) FGameplayTag Tag_Example;
	
};
