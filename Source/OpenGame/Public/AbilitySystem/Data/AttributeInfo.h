// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"
#include "AttributeInfo.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FOpenAttributeInfo
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayTag AttributeTag = FGameplayTag();	// FGameplayTag() => 비어있는 상태

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		FText AttributeName = FText();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		FText AttributeDescription = FText();

	UPROPERTY(BlueprintReadOnly)
		float AttributeValue = 0.f;
};

UCLASS()
class OPENGAME_API UAttributeInfo : public UDataAsset
{
	GENERATED_BODY()

public:
	FOpenAttributeInfo FindAttributeInfoForTag(const FGameplayTag& AttributeTag, bool bLogNotFound = false) const;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		TArray<FOpenAttributeInfo> AttributeInformation;
};
