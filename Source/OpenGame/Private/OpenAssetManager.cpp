// Fill out your copyright notice in the Description page of Project Settings.


#include "OpenAssetManager.h"
#include "OpenGameplayTags.h"

UOpenAssetManager& UOpenAssetManager::Get()
{
	check(GEngine);

	UOpenAssetManager* OpenAssetManager = Cast<UOpenAssetManager>(GEngine->AssetManager);
	return *OpenAssetManager;
}

void UOpenAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();

	FOpenGameplayTags::InitializeNativeGameplayTags();
}
