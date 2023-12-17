// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/OpenPlayerHUD.h"

#include "UI/Widget/OpenUserWidget.h"
#include "UI/WidgetController/OverlayWidgetController.h"
#include "UI/WidgetController/AttributeMenuWidgetController.h"

UOverlayWidgetController* AOpenPlayerHUD::GetOverlayWidgetController(const FWidgetControllerParams& WCParams)
{
	Super::BeginPlay();
	// OverlayWidget을 생성하는 부분
	if (OverlayWidgetController == nullptr)
	{
		OverlayWidgetController = NewObject<UOverlayWidgetController>(this, OverlayWidgetControllerClass);
		// OverlayWidgetController(자손) - CombatWidgetController(부모)이기 때문에
		// CombatWidgetController(부모)의 함수인 SetWidgetControllerParams()를 사용하여 데이터를 채워준다.
		OverlayWidgetController->SetWidgetControllerParams(WCParams);

		// InitOverlay()에서 WidgetController를 생성할 때 GetOverlayWidgetControllerI()를 호출하게 되는데
		// 4개의 AbilitySystem(AS, ASC, PC, PS)가 설정이 되고 난 후, 
		// 스탯에 변화가 생기면 BindCallbacksToDependencies()에 의해 Delegate가 호출되고,
		// 값을 변경하고 그 OverlayWidgetController()를 넘겨준다. 
		OverlayWidgetController->BindCallbacksToDependencies();
	}
	return OverlayWidgetController;
}

UAttributeMenuWidgetController* AOpenPlayerHUD::GetAttributeMenuWidgetController(const FWidgetControllerParams& WCParams)
{
	Super::BeginPlay();
	// OverlayWidget을 생성하는 부분
	if (AttributeMenuWidgetController == nullptr)
	{
		AttributeMenuWidgetController = NewObject<UAttributeMenuWidgetController>(this, AttributeMenuWidgetControllerClass);
		AttributeMenuWidgetController->SetWidgetControllerParams(WCParams);
		AttributeMenuWidgetController->BindCallbacksToDependencies();
	}
	return AttributeMenuWidgetController;
}

// Construct & Set (Widget & WidgetController) + AddToViewport 
// InitOverlay에 필요한 데이터(PlayerConroller, PlayState, AbilitySystemComponent, AttributeState)
void AOpenPlayerHUD::InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS)
{
	// 각 UObjectClass가 존재하는지 checkf 하고 없다면 관련 로그 출력
	checkf(OverlayWidgetClass, TEXT("Overlay Widget Class uninitialized, please fill out BP_AuraHUD"));
	checkf(OverlayWidgetControllerClass, TEXT("Overlay Widget Controller Class uninitialized, please fill out BP_AuraHUD"));

	// UUserWidget 형식으로 Widget을 생성하고
	UUserWidget* Widget	 = CreateWidget<UUserWidget>(GetWorld(), OverlayWidgetClass);
	OverlayWidget = Cast<UOpenUserWidget>(Widget); // 캐스팅

	// 매개변수가 존재하는 Construct로 Struct를 생성
	const FWidgetControllerParams WidgetControllerParams(PC, PS, ASC, AS);
	// OverlayWidgetController를 Get()함수를 통해 가져와서 생성(세팅)
	UOverlayWidgetController* WidgetController = GetOverlayWidgetController(WidgetControllerParams);

	// WIdgetController를 가지고 있고, Setting을 하며
	// 블루프린트 에디터와 Binding
	// => SetWidgetController를 타고 가면, WidgetControllerSet()를 호출하고
	// WIdgetControllerSet Event가 발생하여 각각의 Widget의 WidgetController를 세팅하게 된다.	
	OverlayWidget->SetWidgetController(WidgetController);
	// 그 이후에 초기값을 Broadcasting
	WidgetController->BroadcastInitialValue();

	Widget->AddToViewport();
}
