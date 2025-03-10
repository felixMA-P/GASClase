
#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "CoreAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

USTRUCT(BlueprintType, Blueprintable)
struct FCoreAttributtes : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	FGameplayAttribute Attribute;

	UPROPERTY(EditAnywhere)
	float AttributeBaseValue;
	
};


UCLASS()
class UTHUB_GAS_API UCoreAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadOnly, Category= "Attributes | CommonSet") FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UCoreAttributeSet, Health);
	
	UPROPERTY(BlueprintReadOnly, Category= "Attributes | CommonSet") FGameplayAttributeData Damage;
	ATTRIBUTE_ACCESSORS(UCoreAttributeSet, Damage);
	
	UPROPERTY(BlueprintReadOnly, Category= "Attributes | CommonSet") FGameplayAttributeData Speed;
	ATTRIBUTE_ACCESSORS(UCoreAttributeSet, Speed);

	UPROPERTY(BlueprintReadOnly, Category= "Attributes | CommonSet") FGameplayAttributeData Strength;
	ATTRIBUTE_ACCESSORS(UCoreAttributeSet, Strength);
	
};
