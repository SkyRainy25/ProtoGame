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
	bool bClickMouse;	// 마우스 클릭을 확인하는 함수.

private:
	void InputClickPressed();
	void InputClickReleased();
	//새로운 목표 위치를 받아서 컨트롤러가 소유한 폰을 그 위치로 이동시키는 함수
	void SetNewDestination(const FVector DestLocation);

	void MoveToMouseCursor();

	IEnemyInterface* LastActor;

	IEnemyInterface* ThisActor;
};
