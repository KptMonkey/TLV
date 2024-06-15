// Copyright Druid Mechanics


#include "TLVOverlayWidgetController.h"

#include "TLV/AbilitySystem/TLVAttributeSet.h"

void UTLVOverlayWidgetController::BroadcastInitialValues()
{
    const UTLVAttributeSet* AuraAttributeSet = CastChecked<UTLVAttributeSet>(AttributeSet);

    OnHealthChanged.Broadcast(AuraAttributeSet->GetHealth());
    OnMaxHealthChanged.Broadcast(AuraAttributeSet->GetMaxHealth());	
}

void UTLVOverlayWidgetController::BindCallbacksToDependencies()
{
    const UTLVAttributeSet* TLVAttributeSet = CastChecked<UTLVAttributeSet>(AttributeSet);
    AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(TLVAttributeSet->GetHealthAttribute()).AddUObject(this, &UTLVOverlayWidgetController::HealthChanged);    
    AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(TLVAttributeSet->GetMaxHealthAttribute()).AddUObject(this, &UTLVOverlayWidgetController::MaxHealthChanged);    
}

void UTLVOverlayWidgetController::HealthChanged(FOnAttributeChangeData const& Data) const
{
    OnHealthChanged.Broadcast(Data.NewValue);

}

void UTLVOverlayWidgetController::MaxHealthChanged(FOnAttributeChangeData const& Data) const
{
    OnMaxHealthChanged.Broadcast(Data.NewValue);
}



