// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "EnvironmentQuery/EnvQueryTypes.h"
#include "SGameModeBase.generated.h"

class UEnvQuery;
class UEnvQueryInstanceBlueprintWrapper;
class UCurveFloat;
class USSaveGame;

/**
 * 
 */
UCLASS()
class ACTIONROGUELIKE_API ASGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

protected:

	FString SlotName;
	
	UPROPERTY()
	USSaveGame* CurrentSaveGame;
	
	UPROPERTY(EditDefaultsOnly, Category = "AI")
	TSubclassOf<AActor> MinionClass;
	
	UPROPERTY(EditDefaultsOnly, Category = "AI")
	UEnvQuery* SpawnBotQuery;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
	UCurveFloat* DifficultyCurve;
	
	FTimerHandle TimerHandle_SpawnBot;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
	float SpawnTimerInterval;

	// Read/write access as we could change this as our difficulty increases via Blueprint
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Credit")
	int32 CreditPerKill;
	
	UPROPERTY(EditDefaultsOnly, Category = "PickUp")
	UEnvQuery* SpawnPickUpQuery;

	/* All pick-up classes used to spawn with Eqs at match start */
	UPROPERTY(EditDefaultsOnly, Category = "PickUp")
	TArray<TSubclassOf<AActor>> PickUpClass;

	/* Distance required between pick-up spawn locations */
	UPROPERTY(EditDefaultsOnly, Category = "PickUp")
	float RequiredPickUpDistance;

	/* Amount of pick-up to spawn during match start */
	UPROPERTY(EditDefaultsOnly, Category = "PickUp")
    int32 DesiredPickUpCount;
	
	UFUNCTION()
	void SpawnBotTimerElapsed();

	UFUNCTION()
	void OnQueryCompleted_Bot(UEnvQueryInstanceBlueprintWrapper* QueryInstance, EEnvQueryStatus::Type QueryStatus);

	UFUNCTION()
	void RespawnPlayerElapsed(AController* Controller);

	UFUNCTION()
	void OnQueryCompleted_PickUp(UEnvQueryInstanceBlueprintWrapper* QueryInstance, EEnvQueryStatus::Type QueryStatus);

public:

	virtual void OnActorKilled(AActor* VictimActor, AActor* Killer);

	ASGameModeBase();

	void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;
	
	virtual void StartPlay() override;

	void HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer);

	UFUNCTION(Exec)
	void KillAll();

	UFUNCTION(BlueprintCallable, Category = "SaveGame")
	void WriteSaveGame();

	void LoadSaveGame();
	
};
