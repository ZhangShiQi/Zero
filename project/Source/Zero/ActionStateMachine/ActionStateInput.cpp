// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionStateInput.h"

UActionStateInput::UActionStateInput()
{}


UActionStateInput::~UActionStateInput()
{}

void UActionStateInput::Init(int max_input_name)
{
	axis.init(max_input_name);
	pressed.init(max_input_name);
	released.init(max_input_name);
}

void UActionStateInput::InputAxis(int name, float axis_value)
{
	axis[name].ExecuteIfBound(axis_value);
}

void UActionStateInput::InputActionPressed(int name)
{
	pressed[name].ExecuteIfBound();
}

void UActionStateInput::InputActionReleased(int name)
{
	released[name].ExecuteIfBound();
}

