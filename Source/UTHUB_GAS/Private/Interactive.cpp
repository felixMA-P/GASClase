
#include "Interactive.h"

#include "GameplayStatesManager.h"
#include "UTHUB_GAS/UTHUB_GASCharacter.h"


AInteractive::AInteractive()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AInteractive::CheckTagCondition(AActor* TagOwner)
{

	if (UCustomAbilitySystemComponent* CASC = TagOwner->FindComponentByClass<UCustomAbilitySystemComponent>())
	{
		FGameplayTagContainer CharacterTag;
		CASC->GetOwnedGameplayTags(CharacterTag);

		FGameplayTag InteractiveTag = FGameplayStatesManager::Get().Tag_InteractEnable;
		if (!CharacterTag.HasTag(InteractiveTag)) return;
	}

	
	// if (IGameplayTagAssetInterface* TagAssetInterface = Cast<IGameplayTagAssetInterface>(TagOwner))
	// {
	//
	// 	FGameplayTagContainer CharacterTag;
	// 	TagAssetInterface->GetOwnedGameplayTags(CharacterTag);
	//
	// 	//FGameplayTag InteractiveTag = FGameplayTag::RequestGameplayTag(TEXT("Gameplay.States.CanInteract"));
	// 	FGameplayTag InteractiveTag = FGameplayStatesManager::Get().Tag_InteractEnable;
	// 	
	// 	if (!CharacterTag.HasTag(InteractiveTag)) return;
	//
	// 	if (!CharacterTag.HasTag(ConditionTag))
	// 	{
	// 		ExecuteAction();
	// 	}
	// }
	
}

void AInteractive::BeginPlay()
{
	Super::BeginPlay();
	
}

void AInteractive::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

