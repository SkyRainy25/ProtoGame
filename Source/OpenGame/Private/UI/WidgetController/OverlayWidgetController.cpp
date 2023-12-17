// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetController/OverlayWidgetController.h"
#include "AbilitySystem/OpenAttributeSet.h"
#include "AbilitySystem/OpenAbilitySystemComponent.h"

void UOverlayWidgetController::BroadcastInitialValue()
{
	// CastChecked => Attribute�� Valid���� Check
	UOpenAttributeSet* OpenAttributeSet = CastChecked<UOpenAttributeSet>(AttributeSet);
	// ������ �ʱⰪ�� Broadcasting
	OnHealthChanged.Broadcast(OpenAttributeSet->GetHealth());
	OnMaxHealthChanged.Broadcast(OpenAttributeSet->GetMaxHealth());
	OnManaChanged.Broadcast(OpenAttributeSet->GetMana());
	OnMaxManaChanged.Broadcast(OpenAttributeSet->GetMaxMana());
}

void UOverlayWidgetController::BindCallbacksToDependencies()
{
	const UOpenAttributeSet* OpenAttributeSet = CastChecked<UOpenAttributeSet>(AttributeSet);

	// GetGameplayAttributeValueChangeDelegate => DECLARE_MULTICAST_DELEGATE_OneParam�� ��ȯ
	// DECLARE_MULTICAST_DELEGATE_OneParam => AddUObject. ���(Dynamic Delegate�� �ƴϴϱ�)
	// DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam => AddDyanamic. ���(Dynamic Multicast�̱� ������)

	// Delegate�� ���� �ش� Attribute(Health�� MaxHealth)�� ���� ���ϸ�, �ݹ��Լ� ȣ��(HealthChanged)
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		OpenAttributeSet->GetHealthAttribute()).AddLambda(
			[this](const FOnAttributeChangeData& Data) 
			{
				OnHealthChanged.Broadcast(Data.NewValue);
			}
		);	// Health

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		OpenAttributeSet->GetMaxHealthAttribute()).AddLambda(
			[this](const FOnAttributeChangeData& Data)
			{
				OnMaxHealthChanged.Broadcast(Data.NewValue);
			}
	);	// MaxHealth

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		OpenAttributeSet->GetManaAttribute()).AddLambda(
			[this](const FOnAttributeChangeData& Data)
			{
				OnManaChanged.Broadcast(Data.NewValue);
			}
	);	// Mana

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		OpenAttributeSet->GetMaxManaAttribute()).AddLambda(
			[this](const FOnAttributeChangeData& Data)
			{
				OnMaxManaChanged.Broadcast(Data.NewValue);
			}
	);	// MaxHealth

	// OpenAbilitySystemComponent.cpp ���� EffectAssetTags.Broadcast(TagContainer)�� ���� ����.
	Cast<UOpenAbilitySystemComponent>(AbilitySystemComponent)->EffectAssetTags.AddLambda(
		[this](const FGameplayTagContainer& AssetTag) 
		{
			for (const FGameplayTag& Tag : AssetTag)
			{
				FGameplayTag MessageTag = FGameplayTag::RequestGameplayTag(FName("Message"));
				if (Tag.MatchesTag(MessageTag))
				{
					// For example, say that Tag = Message.HealthPotion
					// "Message.HealthPotion".MatchesTag("Message") will return True, 
					// //"Message".MatchesTag("Message.HealthPotion") will return False
					// Message.HealthPortion(A.1)�� Message(A)������(true) / A.1�� A�̴�
					// Message(A)�� Message.HealthPortion(A.1)�� �ƴϴ�(false)	/ A�� A.1�� �ƴ� ���� ����.
					// �� ���� ����.
					
					// (*) template Function �̱� ������, T�� ������ ����������Ѵ�.
					// < ������ ������ Ÿ�� >
					FUIWidgetRow* Row = GetDataTableRowByTag<FUIWidgetRow>(MessageWidgetDataTable, Tag);
					// �ش� GameplayTag�� �ִ� Row�� ã��, 
					// �� Row�� �ִ� ������ struct FUIWidgetRow�� ����.
					MessageWidgetRowDelegate.Broadcast(*Row);
				}
			}
		}
	);
}

