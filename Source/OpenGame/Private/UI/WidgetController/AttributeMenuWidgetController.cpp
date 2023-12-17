// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetController/AttributeMenuWidgetController.h"

#include "AbilitySystem/OpenAttributeSet.h"
//#include "AbilitySystem/Data/AttributeInfo.h"
#include "OpenGameplayTags.h"

void UAttributeMenuWidgetController::BroadcastInitialValue()
{

}

void UAttributeMenuWidgetController::BindCallbacksToDependencies()
{
	UOpenAttributeSet* AS = Cast<UOpenAttributeSet>(AttributeSet);
	check(AttributeInfo);

	FOpenAttributeInfo Info = AttributeInfo->FindAttributeInfoForTag(FOpenGameplayTags::Get().Attributes_Primary_Strength);
	Info.AttributeValue = AS->GetStrength();
	AttributeInfoDelegate.Broadcast(Info);
}