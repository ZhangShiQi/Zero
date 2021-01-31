// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterZero.h"

ACharacterZero::ACharacterZero()
{
	state_machine = CreateDefaultSubobject<UActionStateMachine>("ActionStateMachine", false);


}

ACharacterZero::~ACharacterZero()
{

}


