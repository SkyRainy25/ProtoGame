// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "UObject/NoExportTypes.h"
#include "OpenWidgetController.generated.h"

class UAttributeSet;
class UAbilitySystemComponent;


USTRUCT(BlueprintType)
struct FWidgetControllerParams
{
	GENERATED_BODY()

		// 4개의 변수(PC, PS, ASC , AS)에 접근해 데이터를 Viewport에 출력하기 위함.
		FWidgetControllerParams() {}

	FWidgetControllerParams(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS)
		: PlayerController(PC), PlayerState(PS), AbilitySystemComponent(ASC), AttributeSet(AS) {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		APlayerController* PlayerController = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		APlayerState* PlayerState = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UAbilitySystemComponent* AbilitySystemComponent = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UAttributeSet* AttributeSet = nullptr;
};
/**
 * 
 */
UCLASS()
class OPENGAME_API UOpenWidgetController: public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void SetWidgetControllerParams(const FWidgetControllerParams& WCParams);

	UFUNCTION(BlueprintCallable)
	virtual void BroadcastInitialValue();
	virtual void BindCallbacksToDependencies();
protected:
	// Data - WidgetController(알고리즘, 및 계산) - WIdget의 구조
	// 아래 4개의 변수에 접근하여 데이터를 계산하고 
	// Widget에 표시.
	UPROPERTY(BlueprintReadOnly, Category = "WidgetController")
		class APlayerController* PlayerController;

	UPROPERTY(BlueprintReadOnly, Category = "WidgetController")
		class APlayerState* PlayerState;

	UPROPERTY(BlueprintReadOnly, Category = "WidgetController")
		class UAbilitySystemComponent* AbilitySystemComponent;

	UPROPERTY(BlueprintReadOnly, Category = "WidgetController")
		class UAttributeSet* AttributeSet;
};
