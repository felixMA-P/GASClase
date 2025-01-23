#pragma once
#include "GameplayTagContainer.h"
#include "GameplayTagsManager.h"


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
		Tag_InteractEnable = UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("GameStates.CanInteract"));
	}

public:
	
	FGameplayTag Tag_InteractEnable;
	
};
