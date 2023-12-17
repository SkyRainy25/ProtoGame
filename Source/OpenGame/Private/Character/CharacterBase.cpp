// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/CharacterBase.h"
#include "AbilitySystemComponent.h"

// Sets default values
ACharacterBase::ACharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Weapon"));
	Weapon->SetupAttachment(GetMesh(), FName("WeaponHandSocket"));

	Bow = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Bow"));
	Bow->SetupAttachment(GetMesh(), FName("WeaponBowSocket"));
}

UAbilitySystemComponent* ACharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

// Called when the game starts or when spawned
void ACharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACharacterBase::InitAbilityActorInfo()
{

}

void ACharacterBase::ApplyEffectToSelf(TSubclassOf<UGameplayEffect> GameplayEffectClass, float Level) const
{
	check(IsValid(GetAbilitySystemComponent()));
	check(GameplayEffectClass);
	// 3. MakeEffectContext()를 이용해서 GameplayEffectContextHandle을 생성.
	FGameplayEffectContextHandle ContextHandle = GetAbilitySystemComponent()->MakeEffectContext();
	ContextHandle.AddSourceObject(this);	// SourceObejct 설정. => 'virtual 'GetPlayerLevel()을 사용하기 위함.
	// 그렇지 않으면 GetSourceObject = nullptr이 나와 Crash 발생
	// 2. MakeOutgoingSpec() => GameplayEffectSpecHandle을 만들기 위해서는
	// GameplayEffectContextHandle & TSubclassOf<UGameplayEffect> 가 필요
	const FGameplayEffectSpecHandle SpecHandle = GetAbilitySystemComponent()->MakeOutgoingSpec(GameplayEffectClass, Level, ContextHandle);
	// 1. GameplayEffectSpecToTarget() 을 사용하기 위해서는 GameplaySpecHandle이 필요
	GetAbilitySystemComponent()->ApplyGameplayEffectSpecToTarget(*SpecHandle.Data.Get(), GetAbilitySystemComponent());

}

void ACharacterBase::InitializeDefaultAttributes() const
{
	ApplyEffectToSelf(DefaultPrimaryAttributes, 1.0f);
	ApplyEffectToSelf(DefaultSecondaryAttributes, 1.0f);
	ApplyEffectToSelf(DefaultVitalAttributes, 1.0f);
}
