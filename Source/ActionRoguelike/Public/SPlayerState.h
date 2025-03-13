// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Delegates/DelegateCombinations.h"
#include "GameFramework/PlayerState.h"
#include "SPlayerState.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnCreditChanged, ASPlayerState*, PlayerState, int32, NewCredit, int32, Delta);

class USSaveGame;
/**
 * 
 */
UCLASS()
class ACTIONROGUELIKE_API ASPlayerState : public APlayerState
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditDefaultsOnly, Category = "Credit")
	int32 Credit;

public:

	UFUNCTION(BlueprintCallable, Category = "Credit")
	int32 GetCredit() const;
	
	UFUNCTION(BlueprintCallable, Category = "Credit")
	void AddCredit(int32 Delta);

	UFUNCTION(BlueprintCallable, Category = "Credit")
	bool RemoveCredit(int32 Delta);

	UPROPERTY(BlueprintAssignable)
    FOnCreditChanged OnCreditChanged;

	UFUNCTION(BlueprintNativeEvent)
	void SavePlayerState(USSaveGame* SaveObject);

	UFUNCTION(BlueprintNativeEvent)
	void LoadPlayerState(USSaveGame* SaveObject);
};
