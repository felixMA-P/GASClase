

#include "DataDriven/GameplayAttributeEffector.h"

#include "CoreAttributeSet.h"
#include "GameplayEffectExtension.h"

void UGameplayAttributeEffector::ApplyAttributeEffector(const FOnAttributeChangeData& InChangedData)
{
	RecieveApplyAttributeEffector(InChangedData.GEModData->Target.GetOwner(), InChangedData.NewValue, InChangedData.OldValue);
	
}
