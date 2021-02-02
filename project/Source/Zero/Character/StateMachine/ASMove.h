// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GameFramework/PawnMovementComponent.h"

#include "ActionStateMachine/ActionStateInput.h"
#include "ActionStateMachine/ActionState.h"

#include "Character/Sprite/FlipbookSprite.h"
#include "Character/CharacterZero.h"

#include "StateInputName.h"
#include "ASMove.generated.h"


UCLASS(Blueprinttype, Blueprintable)
class ZERO_API UActionStateMove : public UActionState
{
	GENERATED_BODY()

public:
	virtual void OnEnter(const ASParam *param) {
		state_input->axis[SIN_Move].BindUObject(this, &UActionStateMove::InputMove);
		state_input->pressed[SIN_Jump].BindUObject(this, &UActionStateMove::InputJumpPressed);
		state_input->released[SIN_Jump].BindUObject(this, &UActionStateMove::InputJumpReleased);

		character = dynamic_cast<ACharacterZero *>(owner);
		movement = character->GetMovementComponent();
		sprite = character->GetSprite();
	}

	virtual void OnExit() {
		state_input->axis[SIN_Move].Unbind();

	}

	virtual void OnUpdate(float delta) {
		if (movement) {
			velocity = owner->GetVelocity();
			is_on_ground = movement->IsMovingOnGround();
			 

			GEngine->AddOnScreenDebugMessage(
				-1, 0, FColor::White,
				FString::Printf(TEXT("Velocity:%s"), *velocity.ToString())
			);
		}
	};

	//
	virtual void InputMove(float axis) {
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

	virtual void InputJumpPressed() {
		if (movement->IsMovingOnGround()) {
			state_machine->ChangeState("ActionStateJump");
		}
	}

	virtual void InputJumpReleased() {

	}

protected:
	UPawnMovementComponent *movement;
	bool is_on_ground;
	FVector velocity;
	UFlipbookSprite *sprite;
	ACharacterZero *character;
	float move_axis;
};

