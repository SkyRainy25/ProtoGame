// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/CharacterBase.h"
#include "PlayerCharacter.generated.h"

/**
 * 
 */
UCLASS()
class OPENGAME_API APlayerCharacter : public ACharacterBase
{
	GENERATED_BODY()
	
public:
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void PostInitializeComponents();

	/** Combat Interface */
	virtual int32 GetPlayerLevel() override;
	/** End Combat Interface */
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void PossessedBy(AController* PlayerController) override;	// Server
	virtual void OnRep_PlayerState() override;	//(V) Client

private:
	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);

protected:

	virtual void InitAbilityActorInfo() override;

private:
	UPROPERTY(EditAnywhere)
		float RotationRate = 10;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* SpringArmComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* Camera;
};
