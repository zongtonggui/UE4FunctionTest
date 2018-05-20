// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TutGameMode.generated.h"

/**
 * 
 */
UCLASS()
class EXPLOREUE4_API ATutGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	ATutGameMode();
	UFUNCTION(BlueprintPure, BlueprintCallable, Category = "Score")
		int32 GetScore();
	
	UFUNCTION(BlueprintCallable, Category = "Score")
		void AddPoints(int32 value);
	UFUNCTION(BlueprintCallable, Category = "Score")
		void DeductPoints(int32 value);
private:

	/**
	* Stores the current score.
	**/
	int32 CurrentScore=10;
	
};
