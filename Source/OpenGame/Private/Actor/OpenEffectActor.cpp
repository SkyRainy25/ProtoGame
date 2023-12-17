// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/OpenEffectActor.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystem/OpenAttributeSet.h"
#include "Components/SphereComponent.h"
// Sets default values
AOpenEffectActor::AOpenEffectActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SetRootComponent(CreateDefaultSubobject<USceneComponent>("SceneRoot"));
}

//void AOpenEffectActor::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
//{
//	// Structure
//// ���� ��� : Actor(or Pawn, Character) -> AbiliySystemComponent -> AttributeSet
////if (IAbilitySystemInterface* ASCInterface = Cast<IAbilitySystemInterface>(OtherActor))
//	{
//		//const UCombatAttributeSet* CombatAttributeSet = Cast<UCombatAttributeSet>(ASCInterface->GetAbilitySystemComponent()->GetAttributeSet(UCombatAttributeSet::StaticClass()));
//
//		//UCombatAttributeSet* MutableCombatAttributeSet = const_cast<UCombatAttributeSet*>(CombatAttributeSet);
//		//MutableCombatAttributeSet->SetHealth(CombatAttributeSet->GetHealth() + 25.f);
//		Destroy();
//	}
//}
//
//void AOpenEffectActor::EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
//{
//}

// Called when the game starts or when spawned
void AOpenEffectActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void AOpenEffectActor::ApplyEffectToTarget(AActor* TargetActor, TSubclassOf<UGameplayEffect> GameplayEffectClass)
{
	UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
	if (TargetASC == nullptr) return;

	check(GameplayEffectClass);	// nullptr ��� Crash
	// TargetASC->MakeOutgoingSpec(GameplayEffectClass, 1.f, EffectContextHandle) �� �ʿ���
	// GameplayEffectContextHandle�� ����.
	// GameplayEffectContextHandle Gameplay�� �ʿ��� �͵��� �����ϰ� �ִ� Wrapper
	FGameplayEffectContextHandle EffectContextHandle = TargetASC->MakeEffectContext();
	// GameplayEffect�� �߱��� ������? (�� ��ü)
	EffectContextHandle.AddSourceObject(this);
	// FGameplayEffectSpecHandle�� EffectSpec�� ���õ� �͵��� �����ϰ� �ִ� Wrapper
	const FGameplayEffectSpecHandle EffectSpecHandle = TargetASC->MakeOutgoingSpec(GameplayEffectClass, 1.f, EffectContextHandle);
	// ApplyGameplayEffectSpecToSelf(������) �̱� ������ Data.Get()�� raw pointer�� ��ȯ�ϹǷ�
	// �տ� *�� �ٿ� ���� �����Ϳ� �����Ͽ� �Ѱ��ش�.
	
	// Ȱ��ȭ�� GameplayEffectHandle�� ����(store).
	FActiveGameplayEffectHandle ActiveEffectHandle = TargetASC->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());
	// EffectSpecHandle.Data.Get()->Def : UGameplayEffect �� ������ Ÿ���� �ǹ�(Def = DeReference)
	
	const bool bIsInfinite = EffectSpecHandle.Data.Get()->Def->DurationPolicy == EGameplayEffectDurationType::Infinite;
	// SpecHandle�� Duration Policy�� Infinite �̸鼭, EndOverlap�� �� ȿ���� ���ŵǾ���ϴ°�?
	// Instant�� Duration�̸� �˾Ƽ� �������� ������, ��� �ڵ嵵 �ʿ����� ����
	if (bIsInfinite && InfiniteEffectRemovalPolicy == EEffectRemovalPolicy::RemoveOnEndOverlap)
	{
		// Ȱ��ȭ�� GameplayEffect�� Handle�� ASC�� Mapping
		ActiveEffectHandles.Add(ActiveEffectHandle, TargetASC);
	}
}

void AOpenEffectActor::OnOverlap(AActor* TargetActor)
{
	if (InstantEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
	{
		ApplyEffectToTarget(TargetActor, InstantGameplayEffectClass);
	}
	if (DurationEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
	{
		ApplyEffectToTarget(TargetActor, DurationGameplayEffectClass);
	}
	if (InfiniteEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
	{
		ApplyEffectToTarget(TargetActor, InfiniteGameplayEffectClass);
	}
}

void AOpenEffectActor::OnEndOverlap(AActor* TargetActor)
{
	if (InstantEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		ApplyEffectToTarget(TargetActor, InstantGameplayEffectClass);
	}
	if (DurationEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		ApplyEffectToTarget(TargetActor, DurationGameplayEffectClass);
	}
	if (InfiniteEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		ApplyEffectToTarget(TargetActor, InfiniteGameplayEffectClass);
	}
	if (InfiniteEffectRemovalPolicy == EEffectRemovalPolicy::RemoveOnEndOverlap)
	{
		UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
		if (!IsValid(TargetASC)) return;

		// for Ž���� �� ��ġ�� Handle�� �����ϱ� ���� TArray�� �����Ͽ� �ӽ� ����.
		TArray<FActiveGameplayEffectHandle> HandlesToRemove;
		for (TTuple<FActiveGameplayEffectHandle, UAbilitySystemComponent*> HandlePair : ActiveEffectHandles)
		{
			// �����ؾ��� ASC(TargetASC)�� HandlePair�� �ִ��� Ȯ���ϴ� ����
			if (TargetASC == HandlePair.Value)
			{
				// ******** ���� *********
				// for ������ ���� Ž���� �̷������ ���� �����͸� �����ϰ� �Ǹ�
				// Crash�� �߻��ϰ� �ȴ�!!!
				TargetASC->RemoveActiveGameplayEffect(HandlePair.Key, 1);
				HandlesToRemove.Add(HandlePair.Key);
			}
		}

		for (FActiveGameplayEffectHandle& Handles : HandlesToRemove)
		{
			// �����ؾ��� Effect�� ã�Ƽ� ����.
			ActiveEffectHandles.FindAndRemoveChecked(Handles);
		}
	}
}


