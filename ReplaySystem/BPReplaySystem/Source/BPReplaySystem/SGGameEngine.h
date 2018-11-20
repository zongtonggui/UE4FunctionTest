// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameEngine.h"
#include "SGGameEngine.generated.h"

/**
 * 
 */
UCLASS()
class BPREPLAYSYSTEM_API USGGameEngine : public UGameEngine
{
	GENERATED_BODY()
public:
	virtual bool Experimental_ShouldPreDuplicateMap(const FName MapName) const { return false; };
};
