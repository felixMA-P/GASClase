
#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "BaseAttack.generated.h"


class AUTHUB_GASCharacter;

UCLASS()
class UTHUB_GAS_API UBaseAttack : public UObject
{
	GENERATED_BODY()

	friend AUTHUB_GASCharacter;
	
	void Attack();
	
public:
	UFUNCTION(BlueprintImplementableEvent)
	void PerformAttack();
};
