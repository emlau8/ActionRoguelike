// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Sound/SoundCue.h"
#include "Components/AudioComponent.h"
#include "SBaseProjectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;
class UParticleSystemComponent;
class USoundCue;

UCLASS(ABSTRACT) // 'Abstract' marks this class as incomplete keeping this out of certain dropdowns windows like SpawnActor in Unreal Editor
class ACTIONROGUELIKE_API ASBaseProjectile : public AActor
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditDefaultsOnly, category = "Effect")
	UParticleSystem* ImpactVFX;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category= "Component")
	USphereComponent* SphereComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category= "Component")
	UProjectileMovementComponent* MovementComp;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, Category= "Component")
	UParticleSystemComponent* EffectComp;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
	USoundCue* ImpactSoundCue;

	// 'virtual' so we can override this in child-classes
	UFUNCTION()
	virtual void OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	//BlueprintNativeEvent = C++ base implement, can be expanded in Blueprints
	// BlueprintCallable to allow child classes to trigger explosions
	// Not required for assigment, useful for expanding in Blueprint later on
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Explode();

	virtual void PostInitializeComponents() override;

public:	
	
	// Sets default values for this actor's properties
	ASBaseProjectile();

};
