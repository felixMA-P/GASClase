

#include "CustomAbilitySystemComponent.h"

#include "CoreAttributeSet.h"
#include "EnhancedInputComponent.h"
#include "DataDriven/GASDataComponent.h"
#include "DataDriven/InputAbilityMapping.h"

UCustomAbilitySystemComponent::UCustomAbilitySystemComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}

template <typename T>
T* UCustomAbilitySystemComponent::GetAttributeSetFromOwner() const
{
	if (!GetOwner()) return nullptr;
	
	TArray<UObject*> OwnerSubObjects;
	GetOwner()->GetDefaultSubobjects(OwnerSubObjects);

	UObject** AttrSet = OwnerSubObjects.FindByPredicate([](const UObject* SubObject)
	{
		return SubObject->IsA(T::StaticClass());
	});

	if (!AttrSet) return nullptr;
	
	return Cast<T>(*AttrSet);
}

void UCustomAbilitySystemComponent::InitAbilityActorInfo(AActor* InOwnerActor, AActor* InAvatarActor)
{
	Super::InitAbilityActorInfo(InOwnerActor, InAvatarActor);
	InitializeAttributtesFromEffects();

	
	
}


void UCustomAbilitySystemComponent::BeginPlay()
{
	Super::BeginPlay();
	InitAbilityActorInfo(GetOwner(), GetOwner());
	
}


void UCustomAbilitySystemComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

FActiveGameplayEffectHandle UCustomAbilitySystemComponent::ApplyGameplayEffect(const TSubclassOf<UGameplayEffect>& EffectClass)
{
	check(EffectClass);
	
	FGameplayEffectContextHandle EffectContextHandle = MakeEffectContext();
	EffectContextHandle.AddSourceObject(this);
	
	const FGameplayEffectSpecHandle Spec = MakeOutgoingSpec(EffectClass, 1, EffectContextHandle);

	return ApplyGameplayEffectSpecToSelf(*Spec.Data.Get());
}

void UCustomAbilitySystemComponent::InitializeAttributtesFromEffects()
{

	if (UGASDataComponent* DataComponent = GetOwner()->FindComponentByClass<UGASDataComponent>())
	{
		for (const TSubclassOf<UGameplayEffect>& EffectClass : DataComponent->AttributeInitializers)
		{
			ApplyGameplayEffect(EffectClass);
		}

	}
}

void UCustomAbilitySystemComponent::AddAbilityFromClass(const TSubclassOf<UGameplayAbility>& AbilityClass)
{

	FGameplayAbilitySpec Spec (AbilityClass, 1, 0);
	GiveAbility(Spec);
	
}

