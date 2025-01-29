// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Sound/SoundCue.h"
#include "Components/AudioComponent.h"
#include "SProjectile_Base.generated.h"

class USphereComponent;
class UProjectileMovementComponent;
class UParticleSystemComponent;
class UAudioComponent;
class USoundCue;

UCLASS(ABSTRACT) // 'Abstract' marks this class as incomplete keeping this out of certain dropdowns windows like SpawnActor in Unreal Editor
class ACTIONROGUELIKE_API ASProjectile_Base : public AActor
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditDefaultsOnly, category = "Effect")
	UParticleSystem* ImpactVFX;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Audio")
	UAudioComponent* FlightSoundComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effect")
	USoundCue* ImpactSoundCue;

	UPROPERTY(EditDefaultsOnly, Category = "Effect")
	TSubclassOf<UCameraShakeBase> CameraShake;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category= "Component")
	USphereComponent* SphereComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category= "Component")
	UProjectileMovementComponent* MovementComp;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, Category= "Component")
	UParticleSystemComponent* EffectComp;

	// 'virtual' so we can override this in child-classes
	UFUNCTION()
	virtual void OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	//BlueprintNativeEvent = C++ base implement, can be expanded in Blueprints
	// BlueprintCallable to allow child classes to trigger explosions
	// Not required for assigment, useful for expanding in Blueprint later on
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Explode();

	virtual void PostInitializeComponents() override;

	UFUNCTION()
	virtual void BeginPlay() override;

public:	
	
	// Sets default values for this actor's properties
	ASProjectile_Base();
	
};
