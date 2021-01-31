// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionStateInput.h"

UActionStateInput::UActionStateInput()
{}


UActionStateInput::~UActionStateInput()
{}


void UActionStateInput::InputMove(float axis)
{
	delegate_input_move.ExecuteIfBound(axis);


}
