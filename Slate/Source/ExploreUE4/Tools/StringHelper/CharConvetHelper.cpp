// Fill out your copyright notice in the Description page of Project Settings.

#include "CharConvetHelper.h"
#include <Regex.h>


bool UCharConvetHelper::CheckStringIsValid(const FString str, const FString Reg)
{
	FRegexPattern Pattern(Reg);
	FRegexMatcher regMatcher(Pattern, str);
	TArray<FString> TagList;						//Split text with <></>, as array elements
	while (true)
	{
		if (!regMatcher.FindNext())
			break;
		FString SingleTagOperation = *regMatcher.GetCaptureGroup(1);
		TagList.Add(SingleTagOperation);
	} 
	return true;
}