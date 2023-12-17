// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/OpenAttributeSet.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "GameFramework/Character.h"
#include "GameplayEffectExtension.h"
#include "Net/UnrealNetwork.h"

UOpenAttributeSet::UOpenAttributeSet()
{
}

// Register Variables for Replication
void UOpenAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// Replication을 할 변수를 등록

	/*
	* Primary Attributes
	*/
	DOREPLIFETIME_CONDITION_NOTIFY(UOpenAttributeSet, Strength, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UOpenAttributeSet, Intelligence, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UOpenAttributeSet, Resilience, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UOpenAttributeSet, Vigor, COND_None, REPNOTIFY_Always);

	/*
	* Secondary Attributes
	*/
	DOREPLIFETIME_CONDITION_NOTIFY(UOpenAttributeSet, Armor, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UOpenAttributeSet, ArmorPenetration, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UOpenAttributeSet, BlockChance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UOpenAttributeSet, CriticalHitChance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UOpenAttributeSet, CriticalHitDamage, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UOpenAttributeSet, CriticalHitResistance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UOpenAttributeSet, HealthRegeneration, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UOpenAttributeSet, ManaRegeneration, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UOpenAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UOpenAttributeSet, MaxMana, COND_None, REPNOTIFY_Always);

	// 특정한 조건 없이(COND_None) Replicate를 하겠다.(REPNOTIFY_Always)
	// REPNOTIRY_OnChange -> 값의 변화가 생길때마다 Replicate(최적화느낌)
	DOREPLIFETIME_CONDITION_NOTIFY(UOpenAttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UOpenAttributeSet, Mana, COND_None, REPNOTIFY_Always);

}

void UOpenAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	if (Attribute == GetHealthAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxHealth());
	}
	if (Attribute == GetManaAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxMana());
	}
}

// GameplayEffect가 작용하여 Attribute를 변화시키고 난 후에 실행.
void UOpenAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	FEffectProperties Props;	// 아웃 파라미터

	// GameplayEffect가 발생했을 떄 관련된 구조체의 정보를 가져와 
	// 아웃파라미터에 저장, 세팅하는 함수.
	SetEffectProperties(Data, Props);
}

void UOpenAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth) const
{
	// AttributeSet , Replicate된 변수, OldValue
	// ABIlitySystem은 RepNotify를 등록하여 변화를 추적한다
	GAMEPLAYATTRIBUTE_REPNOTIFY(UOpenAttributeSet, Health, OldHealth);
}

void UOpenAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UOpenAttributeSet, MaxHealth, OldMaxHealth);
}

void UOpenAttributeSet::OnRep_Mana(const FGameplayAttributeData& OldMana) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UOpenAttributeSet, Mana, OldMana);
}

void UOpenAttributeSet::OnRep_Strength(const FGameplayAttributeData& OldStrength) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UOpenAttributeSet, Strength, OldStrength);
}

void UOpenAttributeSet::OnRep_Intelligence(const FGameplayAttributeData& OldIntelligence) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UOpenAttributeSet, Intelligence, OldIntelligence);

}

void UOpenAttributeSet::OnRep_Resilience(const FGameplayAttributeData& OldResilience) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UOpenAttributeSet, Resilience, OldResilience);

}

void UOpenAttributeSet::OnRep_Vigor(const FGameplayAttributeData& OldVigor) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UOpenAttributeSet, Vigor, OldVigor);

}

void UOpenAttributeSet::OnRep_Armor(const FGameplayAttributeData& OldArmor) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UOpenAttributeSet, Armor, OldArmor);

}

void UOpenAttributeSet::OnRep_ArmorPenetration(const FGameplayAttributeData& OldArmorPenetration) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UOpenAttributeSet, ArmorPenetration, OldArmorPenetration);

}

void UOpenAttributeSet::OnRep_BlockChance(const FGameplayAttributeData& OldBlockChance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UOpenAttributeSet, BlockChance, OldBlockChance);

}

void UOpenAttributeSet::OnRep_CriticalHitChance(const FGameplayAttributeData& OldCriticalHitChance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UOpenAttributeSet, CriticalHitChance, OldCriticalHitChance);

}

void UOpenAttributeSet::OnRep_CriticalHitDamage(const FGameplayAttributeData& OldCriticalHitDamage) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UOpenAttributeSet, CriticalHitDamage, OldCriticalHitDamage);

}

void UOpenAttributeSet::OnRep_CriticalHitResistance(const FGameplayAttributeData& OldCriticalHitResistance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UOpenAttributeSet, CriticalHitResistance, OldCriticalHitResistance);

}

void UOpenAttributeSet::OnRep_HealthRegeneration(const FGameplayAttributeData& OldHealthRegeneration) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UOpenAttributeSet, HealthRegeneration, OldHealthRegeneration);
}

void UOpenAttributeSet::OnRep_ManaRegeneration(const FGameplayAttributeData& OldManaRegeneration) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UOpenAttributeSet, ManaRegeneration, OldManaRegeneration);
}

void UOpenAttributeSet::OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UOpenAttributeSet, MaxMana, OldMaxMana);
}

void UOpenAttributeSet::SetEffectProperties(const FGameplayEffectModCallbackData& Data, FEffectProperties& Props) const
{
	// Source = causer of the effect, Target = target of the effect (owner of this AS)

	// GameplayEffect가 발생할 때, 생성된 Context를 가져와서 Props에 임시 저장.
	Props.EffectContextHandle = Data.EffectSpec.GetContext();
	Props.SourceASC = Props.EffectContextHandle.GetOriginalInstigatorAbilitySystemComponent();

	// TSharedPtr<클래스 > => 'Wrapper'(포인터) 이기 때문에, Get()을 통해 데이터에 접근.

	// ASC + AbilityActorInfo + AvatarActor 모두 Valid? 
	if (IsValid(Props.SourceASC) && Props.SourceASC->AbilityActorInfo.IsValid() && Props.SourceASC->AbilityActorInfo->AvatarActor.IsValid())
	{
		Props.SourceAvatarActor = Props.SourceASC->AbilityActorInfo->AvatarActor.Get();
		Props.SourceController = Props.SourceASC->AbilityActorInfo->PlayerController.Get();
		// Actor가 있지만 Controller가 없으면 Controller를 가져와서 세팅.
		if (Props.SourceController == nullptr && Props.SourceAvatarActor != nullptr)
		{
			if (const APawn* Pawn = Cast<APawn>(Props.SourceAvatarActor))
			{
				Props.SourceController = Pawn->GetController();
			}
		}
		// Controller가 있다면
		if (Props.SourceController)
		{
			// AvatorActor를 Character로 캐스팅.
			ACharacter* SourceCharacter = Cast<ACharacter>(Props.SourceController->GetPawn());
		}
	}

	// Data.Target에 대한 정보를 채워줌.
	if (Data.Target.AbilityActorInfo.IsValid() && Data.Target.AbilityActorInfo->AvatarActor.IsValid())
	{
		Props.TargetAvatarActor = Data.Target.AbilityActorInfo->AvatarActor.Get();
		Props.TargetController = Data.Target.AbilityActorInfo->PlayerController.Get();
		Props.TargetCharacter = Cast<ACharacter>(Props.TargetAvatarActor);
		Props.TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Props.TargetAvatarActor);
	}
}
