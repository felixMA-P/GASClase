

#include "CustomAbilitySystemComponent.h"

UCustomAbilitySystemComponent::UCustomAbilitySystemComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void UCustomAbilitySystemComponent::InitAbilityActorInfo(AActor* InOwnerActor, AActor* InAvatarActor)
{
	Super::InitAbilityActorInfo(InOwnerActor, InAvatarActor);

	//Init stuff
	
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

