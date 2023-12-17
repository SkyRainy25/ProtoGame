// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widget/OpenUserWidget.h"

void UOpenUserWidget::SetWidgetController(UObject* InWidgetController)
{
	WidgetController = InWidgetController;
	WidgetControllerSet();
}