// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SAttributeComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnHealthChanged, AActor*, InstigatorActor, USAttributeComponent*, OwningComp, float, NewHealth, float, ActualDelta);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ACTIONROGUELIKE_API USAttributeComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	UFUNCTION(BlueprintCallable, Category = "Attributes")
	static USAttributeComponent* GetAttributes(AActor* FromActor);

	UFUNCTION(BlueprintCallable, Category = "Attributes", meta = (DisplayName = "IsAlive"))
	static bool IsActorAlive(AActor* Actor);
	
	USAttributeComponent();

protected:

	// Edit Anywhere - edit in BP editor and per-instance in level.
	// VisibleAnywhere - 'read-only' in editor and level, (Use for Components)
	// EditDefaultsOnly - hide variable per-instance, edit un BP editor only
	// VisibleDefaultsOnly - 'read-only' access for variable, only un BP editor (uncommon)
	// EditInstanceOnly - Allow only editing of instance (eg. when placed in level)
	// --
	// BlueprintReadOnly - read-only in the Blueprint scripting (does not affect 'details'-panel)
	// BlueprintReadWrite - read-write access in Blueprints
	//--
	// Category = "" - display only for detail panels and Blueprints context menu.
	
		UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Replicated, Category = "Attributes")
    	float Health;
    	
    	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Replicated, Category = "Attributes")
    	float HealthMax;
	
	// HealthMax, Stamina, Strength

	//UPROPERTY(ReplicatedUsing = "")
	//bool bIsAlive;
	
	UFUNCTION(NetMulticast, Reliable) // @FIXME : mark as Unreliable once we moved the 'state' out of SCharacter
	void MulticastHealthChanged(AActor* InstigatorActor, float NewHealth, float Delta);


public:

	UFUNCTION(BlueprintCallable)
	bool Kill(AActor*InstigatorActor);
	
	UFUNCTION(BlueprintCallable)
	bool IsAlive() const;
	
	UFUNCTION(BlueprintCallable)
	bool IsFullHealth() const;

	UFUNCTION(BlueprintCallable)
	bool IsLowHealth() const;

	UFUNCTION(BlueprintCallable)
	float GetHealthMax() const;

	UPROPERTY(BlueprintAssignable)
	FOnHealthChanged OnHealthChanged;

	UFUNCTION(BlueprintCallable, Category = "Attributes")
	bool ApplyHealthChange(AActor* InstigatorActor, float Delta);
	
};
