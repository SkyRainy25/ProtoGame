// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/CharacterBase.h"
#include "Interaction/EnemyInterface.h"
#include "EnemyCharacter.generated.h"

/**
 * 
 */
UCLASS()
class OPENGAME_API AEnemyCharacter : public ACharacterBase, public IEnemyInterface
{
	GENERATED_BODY()
	
public:
	AEnemyCharacter();

	/** Combat Interface */
	virtual int32 GetPlayerLevel() override;
	/** End Combat Interface */

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void InitAbilityActorInfo() override;
public:

	/** EnemyInterface */
	// ���� �����Լ�(HighlightActor��)�� override���� ������
	// -> �߻� Ŭ������ �ν��Ͻ�ȭ�� �� �����ϴ�. ���� �߻�.
	virtual void HighlightActor() override;
	virtual void UnHighlightActor() override;
	// �����Լ��� �����θ� �ۼ����� ������ 
	// Ȯ���� �� ���� �ܺ� �����Դϴ� => ���� �߻�
	/** --------EnemyInterface */

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Class Defaults")
	int32 Level = 1;

public:
	UPROPERTY(BlueprintReadOnly)
		bool bHighlighted = false;
};
