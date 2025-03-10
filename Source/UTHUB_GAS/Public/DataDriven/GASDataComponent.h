// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "Components/ActorComponent.h"
#include "GASDataComponent.generated.h"


class UInputAbilityMapping;
class UGameplayAttributeEffector;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class UTHUB_GAS_API UGASDataComponent : public UActorComponent
{
	GENERATED_BODY()

	

public:
	UGASDataComponent();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Data", Meta = (AllowPrivateAccess = "true"))
	UDataTable* DT_CoreStats;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Data", Meta = (AllowPrivateAccess = "true"))
	TArray<TSubclassOf<class UGameplayEffect>> AttributeInitializers;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Data", Meta = (AllowPrivateAccess = "true"))
	TMap<FGameplayAttribute, TSubclassOf<UGameplayAttributeEffector>> AttributeEffectors;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Data")
	UInputAbilityMapping* InputAbilityMapping;
	
protected:
	virtual void BeginPlay() override;

	

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
};
