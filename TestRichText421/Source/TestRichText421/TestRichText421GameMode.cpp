// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "TestRichText421GameMode.h"
#include "TestRichText421Character.h"
#include "UObject/ConstructorHelpers.h"

ATestRichText421GameMode::ATestRichText421GameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
