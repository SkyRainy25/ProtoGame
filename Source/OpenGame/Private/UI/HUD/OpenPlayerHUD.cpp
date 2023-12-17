// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/OpenPlayerHUD.h"

#include "UI/Widget/OpenUserWidget.h"
#include "UI/WidgetController/OverlayWidgetController.h"
#include "UI/WidgetController/AttributeMenuWidgetController.h"

UOverlayWidgetController* AOpenPlayerHUD::GetOverlayWidgetController(const FWidgetControllerParams& WCParams)
{
	Super::BeginPlay();
	// OverlayWidget�� �����ϴ� �κ�
	if (OverlayWidgetController == nullptr)
	{
		OverlayWidgetController = NewObject<UOverlayWidgetController>(this, OverlayWidgetControllerClass);
		// OverlayWidgetController(�ڼ�) - CombatWidgetController(�θ�)�̱� ������
		// CombatWidgetController(�θ�)�� �Լ��� SetWidgetControllerParams()�� ����Ͽ� �����͸� ä���ش�.
		OverlayWidgetController->SetWidgetControllerParams(WCParams);

		// InitOverlay()���� WidgetController�� ������ �� GetOverlayWidgetControllerI()�� ȣ���ϰ� �Ǵµ�
		// 4���� AbilitySystem(AS, ASC, PC, PS)�� ������ �ǰ� �� ��, 
		// ���ȿ� ��ȭ�� ����� BindCallbacksToDependencies()�� ���� Delegate�� ȣ��ǰ�,
		// ���� �����ϰ� �� OverlayWidgetController()�� �Ѱ��ش�. 
		OverlayWidgetController->BindCallbacksToDependencies();
	}
	return OverlayWidgetController;
}

UAttributeMenuWidgetController* AOpenPlayerHUD::GetAttributeMenuWidgetController(const FWidgetControllerParams& WCParams)
{
	Super::BeginPlay();
	// OverlayWidget�� �����ϴ� �κ�
	if (AttributeMenuWidgetController == nullptr)
	{
		AttributeMenuWidgetController = NewObject<UAttributeMenuWidgetController>(this, AttributeMenuWidgetControllerClass);
		AttributeMenuWidgetController->SetWidgetControllerParams(WCParams);
		AttributeMenuWidgetController->BindCallbacksToDependencies();
	}
	return AttributeMenuWidgetController;
}

// Construct & Set (Widget & WidgetController) + AddToViewport 
// InitOverlay�� �ʿ��� ������(PlayerConroller, PlayState, AbilitySystemComponent, AttributeState)
void AOpenPlayerHUD::InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS)
{
	// �� UObjectClass�� �����ϴ��� checkf �ϰ� ���ٸ� ���� �α� ���
	checkf(OverlayWidgetClass, TEXT("Overlay Widget Class uninitialized, please fill out BP_AuraHUD"));
	checkf(OverlayWidgetControllerClass, TEXT("Overlay Widget Controller Class uninitialized, please fill out BP_AuraHUD"));

	// UUserWidget �������� Widget�� �����ϰ�
	UUserWidget* Widget	 = CreateWidget<UUserWidget>(GetWorld(), OverlayWidgetClass);
	OverlayWidget = Cast<UOpenUserWidget>(Widget); // ĳ����

	// �Ű������� �����ϴ� Construct�� Struct�� ����
	const FWidgetControllerParams WidgetControllerParams(PC, PS, ASC, AS);
	// OverlayWidgetController�� Get()�Լ��� ���� �����ͼ� ����(����)
	UOverlayWidgetController* WidgetController = GetOverlayWidgetController(WidgetControllerParams);

	// WIdgetController�� ������ �ְ�, Setting�� �ϸ�
	// �������Ʈ �����Ϳ� Binding
	// => SetWidgetController�� Ÿ�� ����, WidgetControllerSet()�� ȣ���ϰ�
	// WIdgetControllerSet Event�� �߻��Ͽ� ������ Widget�� WidgetController�� �����ϰ� �ȴ�.	
	OverlayWidget->SetWidgetController(WidgetController);
	// �� ���Ŀ� �ʱⰪ�� Broadcasting
	WidgetController->BroadcastInitialValue();

	Widget->AddToViewport();
}
