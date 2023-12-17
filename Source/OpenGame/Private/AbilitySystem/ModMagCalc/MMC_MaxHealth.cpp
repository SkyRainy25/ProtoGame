// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/ModMagCalc/MMC_MaxHealth.h"
#include "AbilitySystem/OpenAttributeSet.h"
#include "Interaction/CombatInterface.h"

UMMC_MaxHealth::UMMC_MaxHealth()
{
	VigorDef.AttributeToCapture = UOpenAttributeSet::GetVigorAttribute();
	VigorDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	VigorDef.bSnapshot = false;

	RelevantAttributesToCapture.Add(VigorDef);
}

float UMMC_MaxHealth::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	const FGameplayTagContainer* SourceTag = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTag = Spec.CapturedTargetTags.GetAggregatedTags();
	
	FAggregatorEvaluateParameters EvaluationParams;
	EvaluationParams.SourceTags = SourceTag;
	EvaluationParams.TargetTags = TargetTag;



	float Vigor = 0.f;
	GetCapturedAttributeMagnitude(VigorDef, Spec, EvaluationParams, Vigor);
	Vigor = FMath::Max(Vigor, 0.f);

	// Health�� Vigor + PlayerLevel�� ������ �Ǿ�� �ϱ� ������,
	// GameplayEffect �� SourceObejct(ex. PlayerCharacter or Enemy)�� ������ �ִٸ� -> ICombatInterface�� ĳ���� ����
	// PlayerCharacter, Enemy => CombatInterface�� ������ �ֱ� ����!
	// CharacterBase ���� public ICombatInterface�� ��ӹ޵��� ��/
	// GetSourceObejct() : UObject Ÿ��
	ICombatInterface* CombatInterface = Cast<ICombatInterface>(Spec.GetContext().GetSourceObject());
	const int32 PlayerLevel = CombatInterface->GetPlayerLevel();
	// Player & Enemy�� ������Ͽ� virtual int32 GetPlayerLevel() override�� ���ǵǾ� �ֱ� ������
	// GetSourceObejct�� SourceObject�� �����̳Ŀ� ���� Virtual Function Table�� �������� 
	// �´� GetPlayerLevel()�� ������
	// �׷��� ���ؼ� CharacterBase.cpp�� ���� ContextHandle.AddSourceObject(this);�� �������.
	// �׷��� ������ GetSourceObject() = nullptr�� �Ǿ� Crash �߻�.

	return 80.f + 2.5f * Vigor + 10.f * PlayerLevel;
}
