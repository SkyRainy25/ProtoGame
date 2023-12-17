// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetController/OpenWidgetController.h"
#include "OverlayWidgetController.generated.h"

USTRUCT(BlueprintType)
struct FUIWidgetRow : public FTableRowBase	// UIWidgetRow를 따라서 DataTable을 생성
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayTag MessageTag = FGameplayTag();	// FGameplayTag() => 구조체 생성자인가????

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText Message = FText();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<class UOpenUserWidget> MessageWidget;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UTexture2D* Image = nullptr;
};

// FOnHealtChangedSignature(뒤의 SIgnature)는 델리게이트라는 알려주기 위함.
// 데이터 형식 : float , NewHealth와 NewMaxHealth의 변화가 생기면 Broadcasting
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAttributeChangedSignature, float, NewValue);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMessageWidgetRowSignature, FUIWidgetRow, Row);
/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class OPENGAME_API UOverlayWidgetController : public UOpenWidgetController
{
	GENERATED_BODY()
public:
	virtual void BroadcastInitialValue() override;
	virtual void BindCallbacksToDependencies() override;

	// FOnHealtChangedSignature : 델리게이트 타입
	// OnHealthChanged : 델리게이트 그 자체.
	// BlueprintAssignable => 블루프린트에서 델리게이트를 바인딩할 수 있다.
	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
		FOnAttributeChangedSignature OnHealthChanged;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
		FOnAttributeChangedSignature OnMaxHealthChanged;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
		FOnAttributeChangedSignature OnManaChanged;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
		FOnAttributeChangedSignature OnMaxManaChanged;

	// 위에서 Delegate를 선언하고, Public에서 Delegate를 정의
	UPROPERTY(BlueprintAssignable, Category = "GAS|Messages")
		FMessageWidgetRowSignature MessageWidgetRowDelegate;
protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Widget Data")
	UDataTable* MessageWidgetDataTable;

	template <typename T>
	T* GetDataTableRowByTag(UDataTable* DataTable, const FGameplayTag& Tag);
};

template <typename T>
T* UOverlayWidgetController::GetDataTableRowByTag(UDataTable* DataTable, const FGameplayTag& Tag)
{
	// RowName을 GameplayTag의 이름과 같게 설정했기 때문에. 
	// Tag.GetName()을 통해서 Row를 찾을 수 있다!!
	return DataTable->FindRow<T>(Tag.GetTagName(), TEXT(""));
	// FindRow<T>() => <T> 는 반환할 데이터의 형식.
}