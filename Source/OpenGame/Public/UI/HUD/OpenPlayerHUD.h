// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "OpenPlayerHUD.generated.h"

class UAttributeSet;
class UAbilitySystemComponent;
class UOverlayWidgetController;
class UCombatUserWidget;
class UAttributeMenuWidgetController;

struct FWidgetControllerParams;
/**
 * 
 */
UCLASS()
class OPENGAME_API AOpenPlayerHUD : public AHUD
{
	GENERATED_BODY()
public:

	UOverlayWidgetController* GetOverlayWidgetController(const FWidgetControllerParams& WCParams);
	
	UAttributeMenuWidgetController* GetAttributeMenuWidgetController(const FWidgetControllerParams& WCParams);

	void InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS);

protected:

private:
	UPROPERTY()
		class UOpenUserWidget* OverlayWidget;

	UPROPERTY(EditAnywhere)
		TSubclassOf<UOpenUserWidget> OverlayWidgetClass;

	UPROPERTY()
		class UOverlayWidgetController* OverlayWidgetController;

	UPROPERTY(EditAnywhere)	// 블루프린트 에디터에서 세팅하기 위한 TSubclass
		TSubclassOf<UOverlayWidgetController> OverlayWidgetControllerClass;

	UPROPERTY()
		UAttributeMenuWidgetController* AttributeMenuWidgetController;

	UPROPERTY(EditAnywhere)	// 블루프린트 에디터에서 세팅하기 위한 TSubclass
		TSubclassOf<UAttributeMenuWidgetController> AttributeMenuWidgetControllerClass;
};
