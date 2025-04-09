
#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "CustomAbilitySystemComponent.generated.h"


UINTERFACE(NotBlueprintable)
class UGameplayTagCustomInterface : public UGameplayTagAssetInterface
{
	GENERATED_BODY()
};

class IGameplayTagCustomInterface : public IGameplayTagAssetInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = GameplayTags)
	virtual void AddTag(const FGameplayTag& InTag) = 0;

	UFUNCTION(BlueprintCallable, Category = GameplayTags)
	virtual void RemoveTag(const FGameplayTag& InTag) = 0;
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class UTHUB_GAS_API UCustomAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	UCustomAbilitySystemComponent();

	virtual void InitAbilityActorInfo(AActor* InOwnerActor, AActor* InAvatarActor) override;

	void AddAbilityFromClass(const TSubclassOf<UGameplayAbility>& AbilityClass);

protected:
	virtual void BeginPlay() override;

	void InitializeAttributtesFromEffects();

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, category = Gameplay)
	FActiveGameplayEffectHandle ApplyGameplayEffect(const TSubclassOf<UGameplayEffect>& EffectClass);

private:
	template <typename T>
	T* GetAttributeSetFromOwner() const;

};
