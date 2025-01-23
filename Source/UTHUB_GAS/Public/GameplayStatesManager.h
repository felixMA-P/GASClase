#pragma once
#include "GameplayTagContainer.h"
#include "GameplayTagsManager.h"

#define DEFINE_NATIVE_GAMEPLAY_TAG(TagVariable, TagName) \
TagVariable = UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT(TagName));

class FGameplayStatesManager : public FNoncopyable
{
	
public:

	static FGameplayStatesManager& Get()
	{
		static FGameplayStatesManager* Singleton;
		
		if (!Singleton)
		{
			Singleton = new FGameplayStatesManager();
		}
		
		return *Singleton;
	}

	void InitGameplayTags()
	{
		DEFINE_NATIVE_GAMEPLAY_TAG(Tag_InteractEnable, "GameStates.CanInteract");
		DEFINE_NATIVE_GAMEPLAY_TAG(Tag_InteractEnable, "Status.Healthy");
		DEFINE_NATIVE_GAMEPLAY_TAG(Tag_InteractEnable, "Status.Contagious");
		DEFINE_NATIVE_GAMEPLAY_TAG(Tag_InteractEnable, "Status.Infected");
	}

public:
	
	FGameplayTag Tag_InteractEnable;
	FGameplayTag Tag_InteractHealthy;
	FGameplayTag Tag_InteractContagious;
	FGameplayTag Tag_InteractInfected;
	
};
