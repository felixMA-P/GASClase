// Copyright Epic Games, Inc. All Rights Reserved.

#include "UTHUB_GASCharacter.h"

#include "CoreAttributeSet.h"
#include "CustomAbilitySystemComponent.h"
#include "GameplayStatesManager.h"
#include "Attack/BaseAttack.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/DecalComponent.h"
#include "Components/CapsuleComponent.h"
#include "DataDriven/GameplayAttributeEffector.h"
#include "DataDriven/GASDataComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "Materials/Material.h"
#include "Engine/World.h"

AUTHUB_GASCharacter::AUTHUB_GASCharacter()
{
	// Set size for player capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true); // Don't want arm to rotate when character does
	CameraBoom->TargetArmLength = 800.f;
	CameraBoom->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Create a camera...
	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Activate ticking in order to update the cursor every frame.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	AbilityComponent = CreateDefaultSubobject<UCustomAbilitySystemComponent>(TEXT("AbilityComponent"));

	CoreAttributes = CreateDefaultSubobject<UCoreAttributeSet>(TEXT("CoreAttributes"));

	GASDataComponent = CreateDefaultSubobject<UGASDataComponent>(TEXT("GASData"));
}

void AUTHUB_GASCharacter::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
}

UAbilitySystemComponent* AUTHUB_GASCharacter::GetAbilitySystemComponent() const
{
	return AbilityComponent;
}

void AUTHUB_GASCharacter::PerformFirstAttack() const
{
	CharacterAttributes->PrimaryAttack->GetDefaultObject<UBaseAttack>()->Attack();
}

void AUTHUB_GASCharacter::GetOwnedGameplayTags(FGameplayTagContainer& TagContainer) const
{
	TagContainer = GameplayStatesTags;
}

void AUTHUB_GASCharacter::AddTag(const FGameplayTag& InTag)
{
	GameplayStatesTags.AddTag(InTag);
}

void AUTHUB_GASCharacter::RemoveTag(const FGameplayTag& InTag)
{
	GameplayStatesTags.RemoveTag(InTag);
}

void AUTHUB_GASCharacter::ApplyGameplayEffect()
{
	AbilityComponent->ApplyGameplayEffect(SampleEffect);
}

void AUTHUB_GASCharacter::SetUpAttributeCallBacks()
{
	if(GASDataComponent)
	{
		for(auto [Attribute, EffectorClass] : GASDataComponent->AttributeEffectors)
		{
			auto & Delegate = AbilityComponent->GetGameplayAttributeValueChangeDelegate(Attribute);

			UGameplayAttributeEffector* Effector = EffectorClass->GetDefaultObject<UGameplayAttributeEffector>();
			
			Delegate.AddUObject(Effector, &UGameplayAttributeEffector::ApplyAttributeEffector);
		}
	}
}

void AUTHUB_GASCharacter::InitializeCharacter()
{
	if (CharacterData)
	{
		TArray<FCharacterAttributes*> OutData;
		
		CharacterData->GetAllRows(TEXT(""), OutData);

		if (!OutData.IsEmpty())
		{
			FCharacterAttributes** Attr = OutData.FindByPredicate([this](FCharacterAttributes* Row)
			{
				return Row->GameplayClassTag.MatchesTag(CharacterClassTag);
			});

			if (Attr) CharacterAttributes = *Attr;
			
		}
	}
}

void AUTHUB_GASCharacter::BeginPlay()
{
	SetUpAttributeCallBacks();
	Super::BeginPlay();
	
}

void AUTHUB_GASCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	
}

void AUTHUB_GASCharacter::PreInitializeComponents()
{
	Super::PreInitializeComponents();

	
}
