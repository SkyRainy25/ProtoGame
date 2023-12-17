// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "OpenAttributeSet.generated.h"

// Init/Set/Get 함수를 사용하기 위한 매크로
// ATTRIBUTE_ACCESSORS(클래스 이름, 변수이름)으로 매크로를 선언하면
// Init변수이름 / Set변수이름 / Get변수이름 함수를 사용할 수 있다.
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)


USTRUCT()
struct FEffectProperties
{
	GENERATED_BODY()

		FEffectProperties() {}

	FGameplayEffectContextHandle EffectContextHandle;

	UPROPERTY()
		UAbilitySystemComponent* SourceASC = nullptr;

	UPROPERTY()
		AActor* SourceAvatarActor = nullptr;

	UPROPERTY()
		AController* SourceController = nullptr;

	UPROPERTY()
		ACharacter* SourceCharacter = nullptr;

	UPROPERTY()
		UAbilitySystemComponent* TargetASC = nullptr;

	UPROPERTY()
		AActor* TargetAvatarActor = nullptr;

	UPROPERTY()
		AController* TargetController = nullptr;

	UPROPERTY()
		ACharacter* TargetCharacter = nullptr;
};

/**
 * 
 */
UCLASS()
class OPENGAME_API UOpenAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
public:
	UOpenAttributeSet();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;
	
	/*
	*  Primary Attributes
	*/
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Strength, Category = "Primary Attributes")
		FGameplayAttributeData Strength;
	ATTRIBUTE_ACCESSORS(UOpenAttributeSet, Strength);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Intelligence, Category = "Primary Attributes")
		FGameplayAttributeData Intelligence;
	ATTRIBUTE_ACCESSORS(UOpenAttributeSet, Intelligence);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Resilience, Category = "Primary Attributes")
		FGameplayAttributeData Resilience;
	ATTRIBUTE_ACCESSORS(UOpenAttributeSet, Resilience);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Vigor, Category = "Primary Attributes")
		FGameplayAttributeData Vigor;
	ATTRIBUTE_ACCESSORS(UOpenAttributeSet, Vigor);

	/*
	* Secondary Attributes
	*/

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Armor, Category = "Secondary Attributes")
		FGameplayAttributeData Armor;
	ATTRIBUTE_ACCESSORS(UOpenAttributeSet, Armor);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_ArmorPenetration, Category = "Secondary Attributes")
		FGameplayAttributeData ArmorPenetration;
	ATTRIBUTE_ACCESSORS(UOpenAttributeSet, ArmorPenetration);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_BlockChance, Category = "Secondary Attributes")
		FGameplayAttributeData BlockChance;
	ATTRIBUTE_ACCESSORS(UOpenAttributeSet, BlockChance);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_CriticalHitChance, Category = "Secondary Attributes")
		FGameplayAttributeData CriticalHitChance;
	ATTRIBUTE_ACCESSORS(UOpenAttributeSet, CriticalHitChance);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_CriticalHitDamage, Category = "Secondary Attributes")
		FGameplayAttributeData CriticalHitDamage;
	ATTRIBUTE_ACCESSORS(UOpenAttributeSet, CriticalHitDamage);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_CriticalHitResistance, Category = "Secondary Attributes")
		FGameplayAttributeData CriticalHitResistance;
	ATTRIBUTE_ACCESSORS(UOpenAttributeSet, CriticalHitResistance);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_HealthRegeneration, Category = "Secondary Attributes")
		FGameplayAttributeData HealthRegeneration;
	ATTRIBUTE_ACCESSORS(UOpenAttributeSet, HealthRegeneration);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_ManaRegeneration, Category = "Secondary Attributes")
		FGameplayAttributeData ManaRegeneration;
	ATTRIBUTE_ACCESSORS(UOpenAttributeSet, ManaRegeneration);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxHealth, Category = "Vital Attributes")
		FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UOpenAttributeSet, MaxHealth);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxMana, Category = "Vital Attributes")
		FGameplayAttributeData MaxMana;
	ATTRIBUTE_ACCESSORS(UOpenAttributeSet, MaxMana);

	/*
	* Vital Attributes
	*/
	UPROPERTY(ReplicatedUsing = OnRep_Health)
		FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UOpenAttributeSet, Health);

	UPROPERTY(ReplicatedUsing = OnRep_Mana)
		FGameplayAttributeData Mana;
	ATTRIBUTE_ACCESSORS(UOpenAttributeSet, Mana);

	// 서버가 변수의 값이 변경되어 클라이언트에 Replicate를 하게 되면
	// 클라이언트는 그 변수에 대한 Replicate Notiry가 호출되게 한다
	// ReplictateUsing = OnRep_변수이름(Replicate Notify)

	// OnRep_Health는 반드시 정의해 주어야 하며
	// UFUNCTION 매크로를 사용해야한다.

	UFUNCTION()
		void OnRep_Health(const FGameplayAttributeData& OldHealth) const;

	UFUNCTION()
		void OnRep_Mana(const FGameplayAttributeData& OldMana) const;

	UFUNCTION()
		void OnRep_Strength(const FGameplayAttributeData& OldStrength) const;

	UFUNCTION()
		void OnRep_Intelligence(const FGameplayAttributeData& OldIntelligence) const;

	UFUNCTION()
		void OnRep_Resilience(const FGameplayAttributeData& OldResilience) const;

	UFUNCTION()
		void OnRep_Vigor(const FGameplayAttributeData& OldVigor) const;

	UFUNCTION()
		void OnRep_Armor(const FGameplayAttributeData& OldArmor) const;

	UFUNCTION()
		void OnRep_ArmorPenetration(const FGameplayAttributeData& OldArmorPenetration) const;

	UFUNCTION()
		void OnRep_BlockChance(const FGameplayAttributeData& OldBlockChance) const;

	UFUNCTION()
		void OnRep_CriticalHitChance(const FGameplayAttributeData& OldCriticalHitChance) const;

	UFUNCTION()
		void OnRep_CriticalHitDamage(const FGameplayAttributeData& OldCriticalHitDamage) const;

	UFUNCTION()
		void OnRep_CriticalHitResistance(const FGameplayAttributeData& OldCriticalHitResistance) const;

	UFUNCTION()
		void OnRep_HealthRegeneration(const FGameplayAttributeData& OldHealthRegeneration) const;

	UFUNCTION()
		void OnRep_ManaRegeneration(const FGameplayAttributeData& OldManaRegeneration) const;

	UFUNCTION()
		void OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const;

	UFUNCTION()
		void OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana) const;

private:

	void SetEffectProperties(const FGameplayEffectModCallbackData& Data, FEffectProperties& Props) const;

};
