// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionState.h"
#include "ActionStateInput.h"
#include "ActionStateMachine.h"
#include "GameFramework/PawnMovementComponent.h"
#include "FlipbookSprite.h"
#include "CharacterZero.h"

void UActionStateMove::OnEnter(const ASParam *param)
{
	state_machine->state_input->delegate_input_move.BindUObject(
		this, &UActionStateMove::InputMove);

	movement = ((ACharacterZero *)owner)->GetMovementComponent();
	sprite = ((ACharacterZero *)owner)->GetSprite();
}

void UActionStateMove::OnExit()
{
	state_machine->state_input->delegate_input_move.Unbind();

}

void UActionStateMove::InputMove(float axis)
{
	move_axis = axis;

	if (movement) {
		movement->AddInputVector(FVector(move_axis, 0, 0), false);

		if (move_axis < -0.01f) {
			sprite->SetWorldScale3D(FVector::OneVector);
		}
		else if (move_axis > 0.01f) {
			sprite->SetWorldScale3D(FVector(-1, 1, 1));
		}
	}
}



///////////////////////////////////////////// idle ///////////////////////////////////////////
void UActionStateIdle::OnEnter(const ASParam *param)
{
	UActionStateMove::OnEnter(param);

	sprite->Play("idle");
}

void UActionStateIdle::InputMove(float axis)
{
	if (fabs(axis) > 0.01f) {
		state_machine->ChangeState("ActionStateRun");
	}
}

///////////////////////////////////////////// run ///////////////////////////////////////////
void UActionStateRun::OnEnter(const ASParam *param)
{
	UActionStateMove::OnEnter(param);

	sprite->Play("run");
}

void UActionStateRun::InputMove(float axis)
{
	if (fabs(axis) <= 0.01f){
		state_machine->ChangeState("ActionStateIdle");
	}
	else {
		UActionStateMove::InputMove(axis);
	}
}