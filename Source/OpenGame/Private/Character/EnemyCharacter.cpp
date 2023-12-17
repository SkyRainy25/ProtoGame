// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/EnemyCharacter.h"

#include "AbilitySystem/OpenAttributeSet.h"
#include "AbilitySystem/OpenAbilitySystemComponent.h"
#include "DrawDebugHelpers.h"


AEnemyCharacter::AEnemyCharacter()
{
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);

	// EnemyClass�� ���				// Player�� ���
	// �� - AbilitySystem ����.			// Pawn-PlayerState - AbilitySyetem ����
	//AbilitySystemComponent = CreateDefaultSubobject<UCombatAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	//AbilitySystemComponent->SetIsReplicated(true);
	// AI�� EnemyChacterClass�� Control �ϱ� ������
	// ReplicationMode => Minimal(Muliplayer, AI-Controlled)
	//AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	//AttributeSet = CreateDefaultSubobject<UCombatAttributeSet>(TEXT("AttributeSet"));

}

int32 AEnemyCharacter::GetPlayerLevel()
{
	return Level;
}

void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	InitAbilityActorInfo();
}

void AEnemyCharacter::InitAbilityActorInfo()
{
	AbilitySystemComponent->InitAbilityActorInfo(this, this);
	Cast<UOpenAbilitySystemComponent>(AbilitySystemComponent)->AbilityActorInfoSet();

}

void AEnemyCharacter::HighlightActor()
{
	bHighlighted = true;

	//DrawDebugSphere(GetWorld(),GetActorLocation(), 20.0f, 12, FColor::Red, false, -1);
}

void AEnemyCharacter::UnHighlightActor()
{
	bHighlighted = false;
}
