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
//// 접근 방식 : Actor(or Pawn, Character) -> AbiliySystemComponent -> AttributeSet
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

	check(GameplayEffectClass);	// nullptr 라면 Crash
	// TargetASC->MakeOutgoingSpec(GameplayEffectClass, 1.f, EffectContextHandle) 에 필요한
	// GameplayEffectContextHandle을 정의.
	// GameplayEffectContextHandle Gameplay에 필요한 것들을 포함하고 있는 Wrapper
	FGameplayEffectContextHandle EffectContextHandle = TargetASC->MakeEffectContext();
	// GameplayEffect를 야기한 원인은? (이 객체)
	EffectContextHandle.AddSourceObject(this);
	// FGameplayEffectSpecHandle는 EffectSpec과 관련된 것들을 포함하고 있는 Wrapper
	const FGameplayEffectSpecHandle EffectSpecHandle = TargetASC->MakeOutgoingSpec(GameplayEffectClass, 1.f, EffectContextHandle);
	// ApplyGameplayEffectSpecToSelf(데이터) 이기 때문에 Data.Get()은 raw pointer를 반환하므로
	// 앞에 *을 붙여 실제 데이터에 접근하여 넘겨준다.
	
	// 활성화된 GameplayEffectHandle을 저장(store).
	FActiveGameplayEffectHandle ActiveEffectHandle = TargetASC->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());
	// EffectSpecHandle.Data.Get()->Def : UGameplayEffect 의 데이터 타입을 의미(Def = DeReference)
	
	const bool bIsInfinite = EffectSpecHandle.Data.Get()->Def->DurationPolicy == EGameplayEffectDurationType::Infinite;
	// SpecHandle의 Duration Policy가 Infinite 이면서, EndOverlap일 때 효과가 제거되어야하는가?
	// Instant나 Duration이면 알아서 없어지기 때문에, 어떠한 코드도 필요하지 않음
	if (bIsInfinite && InfiniteEffectRemovalPolicy == EEffectRemovalPolicy::RemoveOnEndOverlap)
	{
		// 활성화된 GameplayEffect의 Handle을 ASC와 Mapping
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

		// for 탐색을 다 마치고 Handle을 삭제하기 위해 TArray를 선언하여 임시 저장.
		TArray<FActiveGameplayEffectHandle> HandlesToRemove;
		for (TTuple<FActiveGameplayEffectHandle, UAbilitySystemComponent*> HandlePair : ActiveEffectHandles)
		{
			// 삭제해야할 ASC(TargetASC)가 HandlePair에 있는지 확인하는 과정
			if (TargetASC == HandlePair.Value)
			{
				// ******** 주의 *********
				// for 구문을 통한 탐색이 이루어지는 동안 데이터를 삭제하게 되면
				// Crash가 발생하게 된다!!!
				TargetASC->RemoveActiveGameplayEffect(HandlePair.Key, 1);
				HandlesToRemove.Add(HandlePair.Key);
			}
		}

		for (FActiveGameplayEffectHandle& Handles : HandlesToRemove)
		{
			// 삭제해야할 Effect를 찾아서 삭제.
			ActiveEffectHandles.FindAndRemoveChecked(Handles);
		}
	}
}


