// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "OpenUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class OPENGAME_API UOpenUserWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
		void SetWidgetController(UObject* InWidgetController);

	UPROPERTY(BlueprintReadOnly)
		class UObject* WidgetController;

protected:
	UFUNCTION(BlueprintImplementableEvent)
		void WidgetControllerSet();
};
