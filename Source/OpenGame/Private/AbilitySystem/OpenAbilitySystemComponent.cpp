// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/OpenAbilitySystemComponent.h"
#include "OpenGameplayTags.h"

void UOpenAbilitySystemComponent::AbilityActorInfoSet()
{
	/** Called on server whenever a GE is applied to self. This includes instant and duration based GEs. */
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &UOpenAbilitySystemComponent::EffectApplied);

	//const FOpenGameplayTags GameplayTags = FOpenGameplayTags::Get();
	
}

void UOpenAbilitySystemComponent::EffectApplied(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle)
{
	FGameplayTagContainer TagContainer;
	EffectSpec.GetAllAssetTags(TagContainer);

	// GameplayEffect를 받으면 Broadcast => OverlayWidgetController로 알림
	EffectAssetTags.Broadcast(TagContainer);
}
