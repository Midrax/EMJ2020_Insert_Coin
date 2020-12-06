// Fill out your copyright notice in the Description page of Project Settings.


#include "TetrisInvaderGameMode.h"

ATetrisInvaderGameMode::ATetrisInvaderGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Characters/InvaderPawn"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
