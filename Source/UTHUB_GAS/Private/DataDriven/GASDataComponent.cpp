

#include "DataDriven/GASDataComponent.h"

#include "GameplayEffectTypes.h"
#include "Abilities/GameplayAbility.h"
#include "DataDriven/InputAbilityMapping.h"

UGASDataComponent::UGASDataComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}


void UGASDataComponent::BeginPlay()
{
	Super::BeginPlay();
	
}




void UGASDataComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                      FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

