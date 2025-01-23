// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "CustomAbilitySystemComponent.h"
#include "GameplayTagContainer.h"
#include "UTHUB_GASCharacter.generated.h"

class UBaseAttack;

USTRUCT(BlueprintType)
struct FCharacterAttributes: public FTableRowBase
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere)
	FGameplayTag GameplayClassTag;
	
	UPROPERTY(EditAnywhere)
	float Health;
	
	UPROPERTY(EditAnywhere)
	float AttackStrength;
	
	UPROPERTY(EditAnywhere)
	float Speed;
	
	UPROPERTY(EditAnywhere)
	UAnimMontage* AttackAnimation;

};


UCLASS(Blueprintable)
class AUTHUB_GASCharacter : public ACharacter, public IAbilitySystemInterface, public IGameplayTagCustomInterface
{
	GENERATED_BODY()
	
public:
	AUTHUB_GASCharacter();

	// Called every frame.
	virtual void Tick(float DeltaSeconds) override;

	/** Returns TopDownCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	FORCEINLINE virtual class UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="GameplayTags")
	FGameplayTag ActiveEventTag;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="GameplayTags")
	FGameplayTagContainer GameplayStatesTags;

	UFUNCTION()
	void PerformFirstAttack();

	virtual void GetOwnedGameplayTags(FGameplayTagContainer& TagContainer) const override;
	virtual void AddTag(const FGameplayTag& InTag) override;
	virtual void RemoveTag(const FGameplayTag& InTag) override;
	

private:
	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* TopDownCameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Ability, meta = (AllowPrivateAccess = "true"))
	class UCustomAbilitySystemComponent* AbilityComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="GameplayTags", Meta = (AllowPrivateAccess = "true"))
	FGameplayTag CharacterClassTag;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Attributes", Meta = (AllowPrivateAccess = "true"))
	FCharacterAttributes* CharacterAttributes;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Attributes", Meta = (AllowPrivateAccess = "true"))
	UDataTable* CharacterData;
	
	void InitializeCharacter();


protected:
	virtual void BeginPlay() override;
	
	UFUNCTION(BlueprintImplementableEvent, Category="GameplayTags")
	void TryInfect();
};

