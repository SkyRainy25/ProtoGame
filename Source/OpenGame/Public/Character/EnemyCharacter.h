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
	// 순수 가상함수(HighlightActor등)을 override하지 않으면
	// -> 추상 클래스를 인스턴스화할 수 없습니다. 오류 발생.
	virtual void HighlightActor() override;
	virtual void UnHighlightActor() override;
	// 가상함수의 구현부를 작성하지 않으면 
	// 확인할 수 없는 외부 참조입니다 => 오류 발생
	/** --------EnemyInterface */

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Class Defaults")
	int32 Level = 1;

public:
	UPROPERTY(BlueprintReadOnly)
		bool bHighlighted = false;
};
