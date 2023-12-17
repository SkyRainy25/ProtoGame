// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetController/OpenWidgetController.h"
#include "OverlayWidgetController.generated.h"

USTRUCT(BlueprintType)
struct FUIWidgetRow : public FTableRowBase	// UIWidgetRow�� ���� DataTable�� ����
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayTag MessageTag = FGameplayTag();	// FGameplayTag() => ����ü �������ΰ�????

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText Message = FText();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<class UOpenUserWidget> MessageWidget;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UTexture2D* Image = nullptr;
};

// FOnHealtChangedSignature(���� SIgnature)�� ��������Ʈ��� �˷��ֱ� ����.
// ������ ���� : float , NewHealth�� NewMaxHealth�� ��ȭ�� ����� Broadcasting
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

	// FOnHealtChangedSignature : ��������Ʈ Ÿ��
	// OnHealthChanged : ��������Ʈ �� ��ü.
	// BlueprintAssignable => �������Ʈ���� ��������Ʈ�� ���ε��� �� �ִ�.
	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
		FOnAttributeChangedSignature OnHealthChanged;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
		FOnAttributeChangedSignature OnMaxHealthChanged;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
		FOnAttributeChangedSignature OnManaChanged;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
		FOnAttributeChangedSignature OnMaxManaChanged;

	// ������ Delegate�� �����ϰ�, Public���� Delegate�� ����
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
	// RowName�� GameplayTag�� �̸��� ���� �����߱� ������. 
	// Tag.GetName()�� ���ؼ� Row�� ã�� �� �ִ�!!
	return DataTable->FindRow<T>(Tag.GetTagName(), TEXT(""));
	// FindRow<T>() => <T> �� ��ȯ�� �������� ����.
}