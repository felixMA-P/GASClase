
#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GameFramework/Actor.h"
#include "Interactive.generated.h"

class UGameplayBaseStateTags;

UCLASS()
class UTHUB_GAS_API AInteractive : public AActor
{
	GENERATED_BODY()

public:
	AInteractive();


	UFUNCTION(BlueprintImplementableEvent)
	void ExecuteAction();

	UFUNCTION(BlueprintCallable)
	void CheckTagCondition(AActor* TagOwner);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Abilities")
	FGameplayTag ConditionTag;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Tags")
	UGameplayBaseStateTags* CharacterStates;
	
protected:

	
	
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
};
