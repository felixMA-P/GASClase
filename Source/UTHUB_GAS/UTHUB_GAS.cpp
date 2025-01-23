// Copyright Epic Games, Inc. All Rights Reserved.

#include "UTHUB_GAS.h"

#include "GameplayStatesManager.h"
#include "Modules/ModuleManager.h"

IMPLEMENT_MODULE(FUTHUB_GAS_MODULE, FUTHUBGASMODULE)
DEFINE_LOG_CATEGORY(LogUTHUB_GAS)

void FUTHUB_GAS_MODULE::StartupModule()
{
	UGameplayTagsManager::OnLastChanceToAddNativeTags().AddLambda([]()
	{
		FGameplayStatesManager::Get().InitGameplayTags();
	});
	
	
}

void FUTHUB_GAS_MODULE::ShutdownModule()
{
	IModuleInterface::ShutdownModule();
}
