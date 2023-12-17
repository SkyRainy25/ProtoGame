// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "OpenAssetManager.generated.h"

/**
 * 
 */
UCLASS()
class OPENGAME_API UOpenAssetManager : public UAssetManager
{
	GENERATED_BODY()
public:

	static UOpenAssetManager& Get();

protected:

	virtual void StartInitialLoading() override;
};
