// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionStateInput.h"

UActionStateInput::UActionStateInput()
{}


UActionStateInput::~UActionStateInput()
{}

void UActionStateInput::InputAxis(const FName &name, float axis_value)
{
	axis[name].ExecuteIfBound(axis_value);
}

void UActionStateInput::InputActionPressed(const FName &name)
{
	pressed[name].ExecuteIfBound();
}

void UActionStateInput::InputActionReleased(const FName &name)
{
	released[name].ExecuteIfBound();
}

