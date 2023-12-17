// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/OpenPlayerState.h"
#include "AbilitySystem/OpenAbilitySystemComponent.h"
#include "AbilitySystem/OpenAttributeSet.h"
#include "Net/UnrealNetwork.h"

AOpenPlayerState::AOpenPlayerState()
{
	AbilitySystemComponent = CreateDefaultSubobject<UOpenAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	// Use Case : Muliplayer, Player-Controlled
	// => Gameplay Effects ard replicated to the owning client only, Gameplay Cues and GameplayTags
	// replicated to all Clients
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	AttributeSet = CreateDefaultSubobject<UOpenAttributeSet>(TEXT("AttributeSet"));

	NetUpdateFrequency = 100;	// ������ Ŭ���̾�Ʈ�� ������Ʈ�ϴ� ������.(����ȭ ����)

}

void AOpenPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AOpenPlayerState, Level);
}

UAbilitySystemComponent* AOpenPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void AOpenPlayerState::OnRep_Level(int32 OldLevel)
{

}

