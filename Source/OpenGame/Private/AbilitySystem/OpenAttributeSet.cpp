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

	// Replication�� �� ������ ���

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

	// Ư���� ���� ����(COND_None) Replicate�� �ϰڴ�.(REPNOTIFY_Always)
	// REPNOTIRY_OnChange -> ���� ��ȭ�� ���涧���� Replicate(����ȭ����)
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

// GameplayEffect�� �ۿ��Ͽ� Attribute�� ��ȭ��Ű�� �� �Ŀ� ����.
void UOpenAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	FEffectProperties Props;	// �ƿ� �Ķ����

	// GameplayEffect�� �߻����� �� ���õ� ����ü�� ������ ������ 
	// �ƿ��Ķ���Ϳ� ����, �����ϴ� �Լ�.
	SetEffectProperties(Data, Props);
}

void UOpenAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth) const
{
	// AttributeSet , Replicate�� ����, OldValue
	// ABIlitySystem�� RepNotify�� ����Ͽ� ��ȭ�� �����Ѵ�
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

	// GameplayEffect�� �߻��� ��, ������ Context�� �����ͼ� Props�� �ӽ� ����.
	Props.EffectContextHandle = Data.EffectSpec.GetContext();
	Props.SourceASC = Props.EffectContextHandle.GetOriginalInstigatorAbilitySystemComponent();

	// TSharedPtr<Ŭ���� > => 'Wrapper'(������) �̱� ������, Get()�� ���� �����Ϳ� ����.

	// ASC + AbilityActorInfo + AvatarActor ��� Valid? 
	if (IsValid(Props.SourceASC) && Props.SourceASC->AbilityActorInfo.IsValid() && Props.SourceASC->AbilityActorInfo->AvatarActor.IsValid())
	{
		Props.SourceAvatarActor = Props.SourceASC->AbilityActorInfo->AvatarActor.Get();
		Props.SourceController = Props.SourceASC->AbilityActorInfo->PlayerController.Get();
		// Actor�� ������ Controller�� ������ Controller�� �����ͼ� ����.
		if (Props.SourceController == nullptr && Props.SourceAvatarActor != nullptr)
		{
			if (const APawn* Pawn = Cast<APawn>(Props.SourceAvatarActor))
			{
				Props.SourceController = Pawn->GetController();
			}
		}
		// Controller�� �ִٸ�
		if (Props.SourceController)
		{
			// AvatorActor�� Character�� ĳ����.
			ACharacter* SourceCharacter = Cast<ACharacter>(Props.SourceController->GetPawn());
		}
	}

	// Data.Target�� ���� ������ ä����.
	if (Data.Target.AbilityActorInfo.IsValid() && Data.Target.AbilityActorInfo->AvatarActor.IsValid())
	{
		Props.TargetAvatarActor = Data.Target.AbilityActorInfo->AvatarActor.Get();
		Props.TargetController = Data.Target.AbilityActorInfo->PlayerController.Get();
		Props.TargetCharacter = Cast<ACharacter>(Props.TargetAvatarActor);
		Props.TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Props.TargetAvatarActor);
	}
}
