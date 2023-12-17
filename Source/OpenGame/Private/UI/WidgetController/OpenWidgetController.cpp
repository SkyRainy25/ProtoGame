// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetController/OpenWidgetController.h"
#include "..\..\..\Public\UI\WidgetController\OpenWidgetController.h"

void UOpenWidgetController::SetWidgetControllerParams(const FWidgetControllerParams& WCParams)
{
	PlayerController = WCParams.PlayerController;
	PlayerState = WCParams.PlayerState;
	AbilitySystemComponent = WCParams.AbilitySystemComponent;
	AttributeSet = WCParams.AttributeSet;
}

void UOpenWidgetController::BroadcastInitialValue()
{

}

void UOpenWidgetController::BindCallbacksToDependencies()
{

}
