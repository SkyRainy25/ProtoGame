// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/PlayerCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Engine/Classes/GameFramework/CharacterMovementComponent.h"

#include "Player/OpenPlayerController.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystem/OpenAbilitySystemComponent.h"
#include "Player/OpenPlayerState.h"
#include "UI/HUD/OpenPlayerHUD.h"

APlayerCharacter::APlayerCharacter()
{
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArmComponent->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArmComponent);

	//// 카메라의 회전에 따라 캐릭터가 회전하지 못하도록 막음.
	//bUseControllerRotationPitch = false;
	//bUseControllerRotationYaw = false;
	//bUseControllerRotationRoll = false;

	//// 캐릭터의 무브먼트를 규정하는 코드
	//// 캐릭터를 이동시키기 전에 이동 방향과 현재 캐릭터의 방향이 다르면
	//// 캐릭터를 이동 방향으로 초당 640도의 회전 속도로 회전시킨다음 이동
	//// 캐릭터의 이동을 평면으로 제한하고, 시작할 때 캐릭터의 위치가 평면을 벗어난 상태라면 
	//// 가까운 평면으로 붙여서 시작되도록 한다. 여기서 평면이란 내비게이션 메시를 의미
	//GetCharacterMovement()->bOrientRotationToMovement = true;
	//GetCharacterMovement()->RotationRate = FRotator(0.0f, 400.0f, 0.0f);
	//GetCharacterMovement()->bConstrainToPlane = true;
	//GetCharacterMovement()->bSnapToPlaneAtStart = true;

	//// 스프링 암의 회전이 월드 좌표계의 회전을 따르도록
	//SpringArmComponent->SetUsingAbsoluteRotation(false);
	//SpringArmComponent->TargetArmLength = 800.0f;
	//SpringArmComponent->SetRelativeRotation(FRotator(-60.0f, 45.0f, 0.0f));
	////bDoCollisionTest는 카메라가 벽에 닿으면 충돌 계산을 통해
	//// 카메라와 캐릭터의 거리를 좁혀 카메라가 벽을 뚫지 않게 만듬
	//SpringArmComponent->bDoCollisionTest = false;

	// 틱함수 작동.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void APlayerCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void APlayerCharacter::Tick(float DeltaTime)
{
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &APlayerCharacter::Jump);	//  점프

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &APlayerCharacter::MoveForward);	//  앞뒤 이동
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &APlayerCharacter::MoveRight);	//  앞뒤 이동
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &APawn::AddControllerPitchInput);	// 상하 회전
	PlayerInputComponent->BindAxis(TEXT("LookRight"), this, &APawn::AddControllerYawInput);	// 좌우 회전
}

void APlayerCharacter::PossessedBy(AController* PlayerController)
{
	Super::PossessedBy(PlayerController);

	// Init ability actor info for the Server
	InitAbilityActorInfo();

}

void APlayerCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	// Init ability actor info for the Client
	InitAbilityActorInfo();
}

void APlayerCharacter::MoveForward(float AxisValue)
{
	// 첫번째
	//  인자 : 나아갈 방향( ForwardVector) 
	// 2번째 인자 : 축 값
	AddMovementInput(GetActorForwardVector() * AxisValue);
}

void APlayerCharacter::MoveRight(float AxisValue)
{
	AddMovementInput(GetActorRightVector() * AxisValue);
}

int32 APlayerCharacter::GetPlayerLevel()
{
	AOpenPlayerState* OpenPlayerState = GetPlayerState<AOpenPlayerState>();
	check(OpenPlayerState);
	return OpenPlayerState->GetPlayerLevel();
}

void APlayerCharacter::InitAbilityActorInfo()
{
	// PlayerState를 Get()함수를 통해 가져오고
	AOpenPlayerState* MyPlayerState = GetPlayerState<AOpenPlayerState>();
	check(MyPlayerState);	// PlayerState의 유효성 검사.

	// Init Ability Actor Info For Server
	// -> PlayerState - Pawn - ASC를 연결
	// Avatar = Pawn(this), Owner = PlayerState
	MyPlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(MyPlayerState, this);

	Cast<UOpenAbilitySystemComponent>(MyPlayerState->GetAbilitySystemComponent())->AbilityActorInfoSet();
	// Get Character's ASC & AS Pointer
	AbilitySystemComponent = MyPlayerState->GetAbilitySystemComponent();
	AttributeSet = MyPlayerState->GetAttributeSet();

	// 앞에서 PlayerState, AbilitySystemComponent, AttribueteSet을 설정해줬고
	// PlayerController(유저)가 Character를 플레이하고 있다면 
	// HUD-> InitOverlay()
	if (AOpenPlayerController* MyPlayerController = Cast<AOpenPlayerController>(GetController()))
	{
		if (AOpenPlayerHUD* UserHUD = Cast<AOpenPlayerHUD>(MyPlayerController->GetHUD()))
		{
			UserHUD->InitOverlay(MyPlayerController, MyPlayerState, AbilitySystemComponent, AttributeSet);
		}
	}
	// 이전에 GetAbilitySystemComponent()를 통해서 ASC가 설정이 되었기 때문에 호출이 가능하며
	// InitAbilityActorInfo처럼 Server & Client 둘다 세팅을 해줘도 되지만
	// Server에서만 실행하여 Client로 Replicate하는 방식도 가능하다.
	InitializeDefaultAttributes();
}
