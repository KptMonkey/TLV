
#include "TLVOverlayWidgetController.h"

#include "TLV/AbilitySystem/TLVAbilitySystemComponent.h"
#include "TLV/AbilitySystem/TLVAttributeSet.h"

void UTLVOverlayWidgetController::BroadcastInitialValues()
{
    auto const TLVAttributeSet = CastChecked<UTLVAttributeSet>(AttributeSet);

    OnHealthChanged.Broadcast(TLVAttributeSet->GetHealth());
    OnMaxHealthChanged.Broadcast(TLVAttributeSet->GetMaxHealth());
    OnStaminaChanged.Broadcast(TLVAttributeSet->GetStamina());
    OnMaxStaminaChanged.Broadcast(TLVAttributeSet->GetMaxStamina());
}

void UTLVOverlayWidgetController::BindCallbacksToDependencies()
{
    const UTLVAttributeSet* TLVAttributeSet = CastChecked<UTLVAttributeSet>(AttributeSet);
    AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(TLVAttributeSet->GetHealthAttribute()).AddUObject(this, &UTLVOverlayWidgetController::HealthChanged);    
    AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(TLVAttributeSet->GetMaxHealthAttribute()).AddUObject(this, &UTLVOverlayWidgetController::MaxHealthChanged);
    AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(TLVAttributeSet->GetStaminaAttribute()).AddUObject(this, &UTLVOverlayWidgetController::StaminaChanged);
    AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(TLVAttributeSet->GetMaxStaminaAttribute()).AddUObject(this, &UTLVOverlayWidgetController::MaxStaminaChanged);
    /*
    Cast<UTLVAbilitySystemComponent>(AbilitySystemComponent)->EffectAssetTags.AddLambda(
    [](FGameplayTagContainer const& TagContainer)
    {
        for (auto const& Tag : TagContainer)
        {
		    GEngine->AddOnScreenDebugMessage(0, 4, FColor::Black, Tag.ToString());
        }
    }
    );
    */
}

void UTLVOverlayWidgetController::HealthChanged(FOnAttributeChangeData const& Data) const
{
    OnHealthChanged.Broadcast(Data.NewValue);

}

void UTLVOverlayWidgetController::MaxHealthChanged(FOnAttributeChangeData const& Data) const
{
    OnMaxHealthChanged.Broadcast(Data.NewValue);
}

void UTLVOverlayWidgetController::StaminaChanged(FOnAttributeChangeData const& data) const
{
    OnStaminaChanged.Broadcast(data.NewValue);
}

void UTLVOverlayWidgetController::MaxStaminaChanged(FOnAttributeChangeData const& data) const
{
    OnMaxStaminaChanged.Broadcast(data.NewValue);
}



