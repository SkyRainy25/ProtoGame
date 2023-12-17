// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/OpenPlayerController.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Interaction/EnemyInterface.h"

AOpenPlayerController::AOpenPlayerController()
{
	// ��Ƽ�÷��̸� ���� ����
	// �ϳ��� ���� ------ �������� Ŭ���̾�Ʈ�� ������Ʈ �� ����.
	bReplicates = true;

	bShowMouseCursor = true; // ���콺 Ŀ�� ���̱�
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

	//bShowMouseCursor = true;	// ���콺 Ŀ�� ���̱�
	//DefaultMouseCursor = EMouseCursor::Default;

	//FInputModeGameAndUI InputModeData;
	//// ViewPort���� ���콺 ��� ����
	//InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);	
	//// ĸ���ϴ� ���� ���콺 ����� ����(���̱�)
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


//���ο� ��ǥ ��ġ�� �޾Ƽ� ��Ʈ�ѷ��� ������ ���� �� ��ġ�� �̵���Ű�� �Լ�
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

// GetHitResultUnderCursor() �Լ��� ���� ���콺 Ŀ�� �Ʒ��� ���� Ʈ���̽��� ���� 
// �� ��ġ�� SetNewDestination() �Լ��� �����ϴ� ������ �Ѵ�.
void AOpenPlayerController::MoveToMouseCursor()
{
	FHitResult Hit;
	GetHitResultUnderCursor(ECC_Visibility, false, Hit);

	if (!Hit.bBlockingHit)
		return;

	LastActor = ThisActor;	// �� Tick���� ThisActor�� LastActo(�ֱپ���)�� ������Ʈ
	ThisActor = Cast<IEnemyInterface>(Hit.GetActor());

	/**
	 * Line trace from cursor. There are several scenarios
	 * 1. LastActor == null / ThisActor == null
	 * - EnemyInterface�� Hit�� �߻����� �ʾ���  => Do nothing
	 * 2. LastActor == null / ThisActor Is Valid
	 *	- �������� ���Ϳ� �浹���� �ʾ�����, ó������ �� ���Ϳ� �浹.
	 *  => HighLight ThisActor
	 * 3. LastActor Is Valid / ThisActor == null
	 * - ���� �����ӿ����� �� ���� Ŀ���� ���� ������, �̹� �����ӿ����� �׷��� ����
	 * =>UnHighLight LastActor
	 * 4. BothActor is Valid, But LastActor is not equal to ThisActor
	 * - ���������ӿ��� LastActor�� ����Ű��, �̹� �����ӿ����� ThisActor�� ����Ŵ.
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
