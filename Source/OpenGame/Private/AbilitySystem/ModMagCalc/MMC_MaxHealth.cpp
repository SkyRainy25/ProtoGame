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

	// Health가 Vigor + PlayerLevel에 연결이 되어야 하기 때문에,
	// GameplayEffect 가 SourceObejct(ex. PlayerCharacter or Enemy)를 가지고 있다면 -> ICombatInterface로 캐스팅 가능
	// PlayerCharacter, Enemy => CombatInterface를 가지고 있기 때문!
	// CharacterBase 에서 public ICombatInterface를 상속받도록 함/
	// GetSourceObejct() : UObject 타입
	ICombatInterface* CombatInterface = Cast<ICombatInterface>(Spec.GetContext().GetSourceObject());
	const int32 PlayerLevel = CombatInterface->GetPlayerLevel();
	// Player & Enemy의 헤더파일에 virtual int32 GetPlayerLevel() override로 정의되어 있기 때문에
	// GetSourceObejct의 SourceObject가 무엇이냐에 따라 Virtual Function Table을 바탕으로 
	// 맞는 GetPlayerLevel()을 가져옴
	// 그러기 위해서 CharacterBase.cpp에 가서 ContextHandle.AddSourceObject(this);를 해줘야함.
	// 그렇지 않으면 GetSourceObject() = nullptr이 되어 Crash 발생.

	return 80.f + 2.5f * Vigor + 10.f * PlayerLevel;
}
