
#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "GameplayAttributeEffector.generated.h"


struct FOnAttributeChangeData;

UCLASS(Blueprintable, BlueprintType)
class UTHUB_GAS_API UGameplayAttributeEffector : public UObject
{
	GENERATED_BODY()

public:

	void ApplyAttributeEffector(const FOnAttributeChangeData& InChangedData);
	
	UFUNCTION(BlueprintImplementableEvent)
	void RecieveApplyAttributeEffector(AActor* InActor, float InNewValue, float InOldValue);
};
