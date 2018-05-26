// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include <ObjectMacros.h>
#include "CharConvetHelper.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class ETagOperationType :uint8
{
	EOpt_Text,
	EOpt_Imgage,
	EOpt_Button
};
USTRUCT(BlueprintType)
struct FHtmlTagInfo
{
	GENERATED_USTRUCT_BODY()
	ETagOperationType Operation;
	TMap<FString, FString> Param;
	FString Content;
};
UCLASS()
class EXPLOREUE4_API UCharConvetHelper : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	static bool   CheckStringIsValid(const FString str, const FString Reg);
	
	
	int a;
	
};
