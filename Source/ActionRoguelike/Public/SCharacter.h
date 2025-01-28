// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SAttributeComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"
#include "SCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class USInteractionComponent;
class UAnimMontage;
class USAttributeComponent;

UCLASS()
class ACTIONROGUELIKE_API ASCharacter : public ACharacter
{
	GENERATED_BODY()

protected:

	/* VisibleAnywhere = read-only, still usefull to view in-editor and enforce a convention. */
	UPROPERTY(VisibleAnywhere, Category = "Effect")
	FName TimeToHitParamName;
	
	UPROPERTY(VisibleAnywhere, Category = "Effect")
	FName HandSocketName;

	UPROPERTY(EditAnywhere, Category = "Attack")
	TSubclassOf<AActor> ProjectileClass;
	
	UPROPERTY(EditAnywhere, Category = "Attack")
	TSubclassOf<AActor> BlackholeClass;

	UPROPERTY(EditAnywhere, Category = "Attack")
	TSubclassOf<AActor> DashClass;

	UPROPERTY(EditAnywhere, Category = "Attack")
	UAnimMontage* AttackAnim;

	/* Particle System played during attack animation */
	UPROPERTY(EditDefaultsOnly, category = "Attack")
	UParticleSystem* CastingEffect;

	FTimerHandle TimerHandle;

	UPROPERTY(EditDefaultsOnly, Category = "Attack")
	float AttackAnimDelay;

	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArmComp;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* CameraComp;

	UPROPERTY(VisibleAnywhere)
	USInteractionComponent* InteractionComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
	USAttributeComponent* AttributeComp;

	void MoveForward(float Value);
	
	void MoveRight(float Value);

	void PrimaryAttack();
	
	void PrimaryAttack_TimeElapsed();

	void Blackhole();
	
	void Blackhole_TimeElapsed();

	void Dash();
	
	void Dash_TimeElapsed();
	
	void SpawnProjectile(TSubclassOf<AActor> SpawnClass);

	void PrimaryInteract();

	void StartAttackEffect();
	
	UFUNCTION()
	void OnHealthChanged(AActor* InstigatorActor, USAttributeComponent* OwningComp, float NewHealth, float HealthMax, float Delta);

	virtual void PostInitializeComponents() override;
	
public:	

	// Sets default values for this character's properties
	ASCharacter();
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};

