// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "OpenPlayerController.generated.h"

/**
 * 
 */

struct FInputActionValue;
class IEnemyInterface;

UCLASS()
class OPENGAME_API AOpenPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	AOpenPlayerController();

	virtual void PlayerTick(float DeltaTime) override;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;


protected:
	bool bClickMouse;	// ���콺 Ŭ���� Ȯ���ϴ� �Լ�.

private:
	void InputClickPressed();
	void InputClickReleased();
	//���ο� ��ǥ ��ġ�� �޾Ƽ� ��Ʈ�ѷ��� ������ ���� �� ��ġ�� �̵���Ű�� �Լ�
	void SetNewDestination(const FVector DestLocation);

	void MoveToMouseCursor();

	IEnemyInterface* LastActor;

	IEnemyInterface* ThisActor;
};
