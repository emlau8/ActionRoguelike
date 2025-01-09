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

	UPROPERTY(EditAnywhere, Category = "Attack")
	TSubclassOf<AActor> ProjectileClass;

	UPROPERTY(EditAnywhere, Category = "Attack")
	UAnimMontage* AttackAnim;

	FTimerHandle TimerHandle;

	UPROPERTY(EditAnywhere, Category = "Blackhole")
	TSubclassOf<AActor> BlackholeClass;

	UPROPERTY(EditAnywhere, Category = "Blackhole")
	UAnimMontage* BlackholeAnim;

	UPROPERTY(EditAnywhere, Category = "Dash")
	TSubclassOf<AActor> DashClass;

	UPROPERTY(EditAnywhere, Category = "Dash")
	UAnimMontage* DashAnim;

public:
	// Sets default values for this character's properties
	ASCharacter();

protected:

	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArmComp;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* CameraComp;

	UPROPERTY(VisibleAnywhere)
	USInteractionComponent* InteractionComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
	USAttributeComponent* AttributesComp;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void MoveForward(float Value);
	
	void MoveRight(float Value);

	void PrimaryAttack();
	
	void PrimaryAttack_TimeElapsed();
	
	void PrimaryInteract();
	
	void SpawnProjectile(TSubclassOf<AActor> SpawnClass);

	void Blackhole();
	
	void Blackhole_TimeElapsed();

	void Dash();
	
	void Dash_TimeElapsed();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};

