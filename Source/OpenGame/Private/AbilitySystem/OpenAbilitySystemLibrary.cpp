// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/OpenAbilitySystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "UI/WidgetController/OpenWidgetController.h"
#include "Player/OpenPlayerState.h"
#include "UI/HUD/OpenPlayerHUD.h"

UOverlayWidgetController* UOpenAbilitySystemLibrary::GetOverlayWidgetController(const UObject* WorldContextObject)
{
	if (APlayerController* PC = UGameplayStatics::GetPlayerController(WorldContextObject, 0))
	{
		if (AOpenPlayerHUD* OpenHUD = Cast<AOpenPlayerHUD>(PC->GetHUD()))
		{
			AOpenPlayerState* PS = PC->GetPlayerState<AOpenPlayerState>();
			UAbilitySystemComponent* ASC = PS->GetAbilitySystemComponent();
			UAttributeSet* AS = PS->GetAttributeSet();

			const FWidgetControllerParams WidgetControllerParams(PC,PS, ASC,AS);
			return OpenHUD->GetOverlayWidgetController(WidgetControllerParams);
			
		}
	}
	return nullptr;
}

UAttributeMenuWidgetController* UOpenAbilitySystemLibrary::GetAttributeMenuWidgetController(const UObject* WorldContextObject)
{
	if (APlayerController* PC = UGameplayStatics::GetPlayerController(WorldContextObject, 0))
	{
		if (AOpenPlayerHUD* OpenHUD = Cast<AOpenPlayerHUD>(PC->GetHUD()))
		{
			AOpenPlayerState* PS = PC->GetPlayerState<AOpenPlayerState>();
			UAbilitySystemComponent* ASC = PS->GetAbilitySystemComponent();
			UAttributeSet* AS = PS->GetAttributeSet();

			const FWidgetControllerParams WidgetControllerParams(PC, PS, ASC, AS);
			return OpenHUD->GetAttributeMenuWidgetController(WidgetControllerParams);

		}
	}
	return nullptr;
}