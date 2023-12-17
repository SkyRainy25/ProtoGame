// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/OpenPlayerController.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Interaction/EnemyInterface.h"

AOpenPlayerController::AOpenPlayerController()
{
	// 멀티플레이를 위한 설정
	// 하나의 서버 ------ 여러개의 클라이언트로 업데이트 에 관한.
	bReplicates = true;

	bShowMouseCursor = true; // 마우스 커서 보이기
}

void AOpenPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	//if (bClickMouse)
	//{
	//	MoveToMouseCursor();
	//}
}

void AOpenPlayerController::BeginPlay()
{
	Super::BeginPlay();

	//bShowMouseCursor = true;	// 마우스 커서 보이기
	//DefaultMouseCursor = EMouseCursor::Default;

	//FInputModeGameAndUI InputModeData;
	//// ViewPort에서 마우스 잠금 해제
	//InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);	
	//// 캡쳐하는 동안 마우스 숨기기 해제(보이기)
	//InputModeData.SetHideCursorDuringCapture(false);
	//SetInputMode(InputModeData);
}

void AOpenPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	/*InputComponent->BindAction("MouseClick", IE_Pressed, this, &AOpenPlayerController::InputClickPressed);
	InputComponent->BindAction("MouseClick", IE_Released, this, &AOpenPlayerController::InputClickReleased);*/
	//InputComponent->BindAxis("MoveForward", this, &AMyPlayerController::InputClickReleased);
}

void AOpenPlayerController::InputClickPressed()
{
	bClickMouse = true;
}

void AOpenPlayerController::InputClickReleased()
{
	bClickMouse = false;
}


//새로운 목표 위치를 받아서 컨트롤러가 소유한 폰을 그 위치로 이동시키는 함수
void AOpenPlayerController::SetNewDestination(const FVector DestLocation)
{
	APawn* const MyPawn = GetPawn();
	if (MyPawn)
	{
		float const Distance = FVector::Dist(DestLocation, MyPawn->GetActorLocation());

		if (Distance > 300.0f)
		{
			UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, DestLocation);
		}
	}
}

// GetHitResultUnderCursor() 함수를 통해 마우스 커서 아래에 레이 트레이스를 쏴서 
// 그 위치를 SetNewDestination() 함수에 전달하는 역할을 한다.
void AOpenPlayerController::MoveToMouseCursor()
{
	FHitResult Hit;
	GetHitResultUnderCursor(ECC_Visibility, false, Hit);

	if (!Hit.bBlockingHit)
		return;

	LastActor = ThisActor;	// 매 Tick마다 ThisActor를 LastActo(최근액터)로 업데이트
	ThisActor = Cast<IEnemyInterface>(Hit.GetActor());

	/**
	 * Line trace from cursor. There are several scenarios
	 * 1. LastActor == null / ThisActor == null
	 * - EnemyInterface에 Hit가 발생하지 않았을  => Do nothing
	 * 2. LastActor == null / ThisActor Is Valid
	 *	- 이전에는 액터에 충돌하지 않았지만, 처음으로 이 액터에 충돌.
	 *  => HighLight ThisActor
	 * 3. LastActor Is Valid / ThisActor == null
	 * - 지난 프레임에서는 적 위를 커서로 갖다 댔지만, 이번 프레임에서는 그렇지 않음
	 * =>UnHighLight LastActor
	 * 4. BothActor is Valid, But LastActor is not equal to ThisActor
	 * - 지난프레임에서 LastActor를 가리키고, 이번 프레임에서는 ThisActor를 가리킴.
	 * => UnHighLight LastActor / HighLight ThisActor
	 * 5. Both Actor Is valid , and are the same Actor
	 * - Do nothing
	**/

	if (LastActor == nullptr)
	{
		if (ThisActor)
		{
			// Case 2
			ThisActor->HighlightActor();
		}
		else
		{
			// Case 1 => Do nothing
		}
	}
	else // LastActor Is Valid
	{
		if (ThisActor)
		{
			if (LastActor != ThisActor)
			{
				// Case 4
				LastActor->UnHighlightActor();
				ThisActor->HighlightActor();
			}
			else
			{
				// Cast5 => Do Nothing.
			}

		}
		else
		{
			// Case 3
			LastActor->UnHighlightActor();
		}
	}

	if (Hit.bBlockingHit)
	{
		SetNewDestination(Hit.ImpactPoint);
	}
}
