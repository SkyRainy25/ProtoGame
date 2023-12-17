// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "EnemyInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UEnemyInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class OPENGAME_API IEnemyInterface
{
	GENERATED_BODY()

		// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	// 순수 가상함수 -> EnemyClass에서 실행할 것.
	// 구현부에서 정의하지 않아도 됨.
	virtual void HighlightActor() = 0;
	virtual void UnHighlightActor() = 0;
};
