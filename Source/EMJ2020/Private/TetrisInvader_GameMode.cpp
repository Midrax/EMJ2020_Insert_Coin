// Fill out your copyright notice in the Description page of Project Settings.


#include "TetrisInvader_GameMode.h"

ATetrisInvader_GameMode::ATetrisInvader_GameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Characters/InvaderPawn"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

}
