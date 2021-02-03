// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GameFramework/PawnMovementComponent.h"

#include "ActionStateMachine/ActionStateInput.h"
#include "ActionStateMachine/ActionState.h"

#include "Character/Sprite/FlipbookSprite.h"
#include "Character/CharacterZero.h"
#include "Character/SideDetectBox.h"

#include "StateInputName.h"
#include "ASMove.generated.h"


UCLASS(Blueprinttype, Blueprintable)
class ZERO_API UActionStateMove : public UActionState
{
	GENERATED_BODY()

public:

public:
	virtual void OnEnter(const ASParam *param) {
		EnableInputMove();
		EnableInputJump();

		character = dynamic_cast<ACharacterZero *>(owner);
		movement = character->GetMovementComponent();
		sprite = character->GetSprite();
		side_box = character->GetSideBox();
	}

	virtual void OnExit() {
		state_input->axis[SIN_Move].Unbind();
		state_input->pressed[SIN_Jump].Unbind();
		state_input->released[SIN_Jump].Unbind();
	}

	virtual void OnUpdate(float delta) {
		if (movement) {
			character->is_on_ground = movement->IsMovingOnGround();

			GEngine->AddOnScreenDebugMessage(
				-1, 0, FColor::White,
				FString::Printf(TEXT("Velocity:%s"), *movement->Velocity.ToString())
			);
		}
	};

	virtual void EnableInputMove() {
		state_input->axis[SIN_Move].BindUObject(this, &UActionStateMove::InputMove);
	}

	virtual void EnableInputJump() {
		state_input->pressed[SIN_Jump].BindUObject(this, &UActionStateMove::InputJumpPressed);
		state_input->released[SIN_Jump].BindUObject(this, &UActionStateMove::InputJumpReleased);
	}

	FORCEINLINE bool IsInputMove()		{ return fabs(move_axis) > 0.01f; }
	FORCEINLINE bool IsInputMoveLeft()	{ return IsInputMove() && move_axis < -0.01f; }
	FORCEINLINE bool IsInputMoveRight() { return IsInputMove() && move_axis >  0.01f; }
	FORCEINLINE EDirection GetInputMoveDir() {
		if (IsInputMoveLeft()) return EDirection::LEFT;
		else if (IsInputMoveRight()) return EDirection::RIGHT;
		else return EDirection::NONE;
	}

	virtual void ChangeSpriteDir(EDirection dir) {
		if (character->sprite_dir != dir && dir != EDirection::NONE) {
			UE_LOG(LogTemp, Log, TEXT("sprite_dir:%d, new_dir:%d"), character->sprite_dir, dir);

			character->sprite_dir = dir;
			if (character->sprite_dir == EDirection::RIGHT) {
				sprite->SetWorldScale3D(FVector(-1, 1, 1));
			}
			else {
				sprite->SetWorldScale3D(FVector::OneVector);
			}
		}
	}

	virtual void InputMove(float axis) {
		move_axis = axis;

		if (movement) {
			movement->AddInputVector(FVector(move_axis, 0, 0), false);

			if (IsInputMoveLeft()) {
				ChangeSpriteDir(EDirection::LEFT);
			}
			else if (IsInputMoveRight()) {
				ChangeSpriteDir(EDirection::RIGHT);
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
	UFlipbookSprite *sprite;
	USideDetectBox *side_box;
	ACharacterZero *character;
	float move_axis;
};

