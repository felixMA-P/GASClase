// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

DECLARE_LOG_CATEGORY_EXTERN(LogUTHUB_GAS, Log, All);

class FUTHUB_GAS_MODULE : public IModuleInterface
{

	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
	
};