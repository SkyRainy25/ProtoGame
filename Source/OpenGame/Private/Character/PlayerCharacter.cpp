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

	//// ī�޶��� ȸ���� ���� ĳ���Ͱ� ȸ������ ���ϵ��� ����.
	//bUseControllerRotationPitch = false;
	//bUseControllerRotationYaw = false;
	//bUseControllerRotationRoll = false;

	//// ĳ������ �����Ʈ�� �����ϴ� �ڵ�
	//// ĳ���͸� �̵���Ű�� ���� �̵� ����� ���� ĳ������ ������ �ٸ���
	//// ĳ���͸� �̵� �������� �ʴ� 640���� ȸ�� �ӵ��� ȸ����Ų���� �̵�
	//// ĳ������ �̵��� ������� �����ϰ�, ������ �� ĳ������ ��ġ�� ����� ��� ���¶�� 
	//// ����� ������� �ٿ��� ���۵ǵ��� �Ѵ�. ���⼭ ����̶� ������̼� �޽ø� �ǹ�
	//GetCharacterMovement()->bOrientRotationToMovement = true;
	//GetCharacterMovement()->RotationRate = FRotator(0.0f, 400.0f, 0.0f);
	//GetCharacterMovement()->bConstrainToPlane = true;
	//GetCharacterMovement()->bSnapToPlaneAtStart = true;

	//// ������ ���� ȸ���� ���� ��ǥ���� ȸ���� ��������
	//SpringArmComponent->SetUsingAbsoluteRotation(false);
	//SpringArmComponent->TargetArmLength = 800.0f;
	//SpringArmComponent->SetRelativeRotation(FRotator(-60.0f, 45.0f, 0.0f));
	////bDoCollisionTest�� ī�޶� ���� ������ �浹 ����� ����
	//// ī�޶�� ĳ������ �Ÿ��� ���� ī�޶� ���� ���� �ʰ� ����
	//SpringArmComponent->bDoCollisionTest = false;

	// ƽ�Լ� �۵�.
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

	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &APlayerCharacter::Jump);	//  ����

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &APlayerCharacter::MoveForward);	//  �յ� �̵�
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &APlayerCharacter::MoveRight);	//  �յ� �̵�
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &APawn::AddControllerPitchInput);	// ���� ȸ��
	PlayerInputComponent->BindAxis(TEXT("LookRight"), this, &APawn::AddControllerYawInput);	// �¿� ȸ��
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
	// ù��°
	//  ���� : ���ư� ����( ForwardVector) 
	// 2��° ���� : �� ��
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
	// PlayerState�� Get()�Լ��� ���� ��������
	AOpenPlayerState* MyPlayerState = GetPlayerState<AOpenPlayerState>();
	check(MyPlayerState);	// PlayerState�� ��ȿ�� �˻�.

	// Init Ability Actor Info For Server
	// -> PlayerState - Pawn - ASC�� ����
	// Avatar = Pawn(this), Owner = PlayerState
	MyPlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(MyPlayerState, this);

	Cast<UOpenAbilitySystemComponent>(MyPlayerState->GetAbilitySystemComponent())->AbilityActorInfoSet();
	// Get Character's ASC & AS Pointer
	AbilitySystemComponent = MyPlayerState->GetAbilitySystemComponent();
	AttributeSet = MyPlayerState->GetAttributeSet();

	// �տ��� PlayerState, AbilitySystemComponent, AttribueteSet�� ���������
	// PlayerController(����)�� Character�� �÷����ϰ� �ִٸ� 
	// HUD-> InitOverlay()
	if (AOpenPlayerController* MyPlayerController = Cast<AOpenPlayerController>(GetController()))
	{
		if (AOpenPlayerHUD* UserHUD = Cast<AOpenPlayerHUD>(MyPlayerController->GetHUD()))
		{
			UserHUD->InitOverlay(MyPlayerController, MyPlayerState, AbilitySystemComponent, AttributeSet);
		}
	}
	// ������ GetAbilitySystemComponent()�� ���ؼ� ASC�� ������ �Ǿ��� ������ ȣ���� �����ϸ�
	// InitAbilityActorInfoó�� Server & Client �Ѵ� ������ ���൵ ������
	// Server������ �����Ͽ� Client�� Replicate�ϴ� ��ĵ� �����ϴ�.
	InitializeDefaultAttributes();
}
