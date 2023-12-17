// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetController/OverlayWidgetController.h"
#include "AbilitySystem/OpenAttributeSet.h"
#include "AbilitySystem/OpenAbilitySystemComponent.h"

void UOverlayWidgetController::BroadcastInitialValue()
{
	// CastChecked => Attribute가 Valid한지 Check
	UOpenAttributeSet* OpenAttributeSet = CastChecked<UOpenAttributeSet>(AttributeSet);
	// 설정한 초기값을 Broadcasting
	OnHealthChanged.Broadcast(OpenAttributeSet->GetHealth());
	OnMaxHealthChanged.Broadcast(OpenAttributeSet->GetMaxHealth());
	OnManaChanged.Broadcast(OpenAttributeSet->GetMana());
	OnMaxManaChanged.Broadcast(OpenAttributeSet->GetMaxMana());
}

void UOverlayWidgetController::BindCallbacksToDependencies()
{
	const UOpenAttributeSet* OpenAttributeSet = CastChecked<UOpenAttributeSet>(AttributeSet);

	// GetGameplayAttributeValueChangeDelegate => DECLARE_MULTICAST_DELEGATE_OneParam를 반환
	// DECLARE_MULTICAST_DELEGATE_OneParam => AddUObject. 사용(Dynamic Delegate가 아니니까)
	// DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam => AddDyanamic. 사용(Dynamic Multicast이기 때문에)

	// Delegate를 통해 해당 Attribute(Health나 MaxHealth)의 값이 변하면, 콜백함수 호출(HealthChanged)
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

	// OpenAbilitySystemComponent.cpp 에서 EffectAssetTags.Broadcast(TagContainer)로 인해 실행.
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
					// Message.HealthPortion(A.1)은 Message(A)이지만(true) / A.1은 A이다
					// Message(A)는 Message.HealthPortion(A.1)이 아니다(false)	/ A는 A.1이 아닐 수도 있음.
					// 논리 구조 문제.
					
					// (*) template Function 이기 때문에, T의 형식을 지정해줘야한다.
					// < 지정할 데이터 타입 >
					FUIWidgetRow* Row = GetDataTableRowByTag<FUIWidgetRow>(MessageWidgetDataTable, Tag);
					// 해당 GameplayTag가 있는 Row를 찾고, 
					// 그 Row에 있는 정보를 struct FUIWidgetRow에 저장.
					MessageWidgetRowDelegate.Broadcast(*Row);
				}
			}
		}
	);
}

