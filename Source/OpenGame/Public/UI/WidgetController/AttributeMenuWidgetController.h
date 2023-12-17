// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetController/OpenWidgetController.h"
#include "AbilitySystem/Data/AttributeInfo.h"
#include "AttributeMenuWidgetController.generated.h"

class UAttributeInfo;
struct FOpenAttributeInfo;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAttributeInfoSignature, const FOpenAttributeInfo&, Info);
/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class OPENGAME_API UAttributeMenuWidgetController : public UOpenWidgetController
{
	GENERATED_BODY()
public:
	virtual void BroadcastInitialValue() override;
	virtual void BindCallbacksToDependencies() override;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FAttributeInfoSignature AttributeInfoDelegate;

protected:
	UPROPERTY(EditDefaultsOnly)
		UAttributeInfo* AttributeInfo;
};
