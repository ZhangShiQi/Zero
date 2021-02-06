// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ASMove.h"
#include "ASSideClimbing.generated.h"


UCLASS(Blueprinttype, Blueprintable)
class ZERO_API UActionStateSideClimbing: public UActionStateMove {
	GENERATED_BODY()
public:

	EDirection last_dir;
	bool need_reverse_dir = false;
	bool change_state_inair = false;
	float wait_change_state = 0.f;

	virtual void OnEnter(const ASParam *param) {
		UActionStateMove::OnEnter(param);
		
		sprite->OnFinishedPlaying.AddDynamic(this, &UActionStateSideClimbing::OnAnimFinished);
		
		sprite->Play("normal_side_climbing");

		last_dir = character->sprite_dir;
		wait_change_state = character->default_side_climbing_down_hold_time;
		change_state_inair = false;
		need_reverse_dir = false;
	}

	virtual void OnExit() {
		UActionStateMove::OnExit();

		sprite->OnFinishedPlaying.RemoveDynamic(this, &UActionStateSideClimbing::OnAnimFinished);
	}

	virtual void OnUpdate(float delta) {
		UActionStateMove::OnUpdate(delta);

		// constraint z axis for velocity.
		movement->Velocity.Z = character->default_side_climbing_speed;

		// 
		if (character->is_on_ground) {
			if (IsInputMove()) {
				state_machine->ChangeState("ActionStateRun");
				return;
			}
			else {
				state_machine->ChangeState("ActionStateIdle");
				return;
			}
		}
		else {
			if (character->sprite_dir != last_dir) {
				state_machine->ChangeState("ActionStateInAir");
				return;
			}
		}

		if (!side_box->IsHit()) {
			state_machine->ChangeState("ActionStateInAir");
			return;
		}

		if (GetInputMoveDir() != last_dir) {
			need_reverse_dir = true;
			change_state_inair = true;
		}

		// hold time.
		if (change_state_inair) {
			wait_change_state -= delta;
			if (wait_change_state <= 0.f) {
				if (need_reverse_dir) {
					ReverseDir();
				}
				state_machine->ChangeState("ActionStateInAir");
			}
			else {
				if (GetInputMoveDir() == last_dir) {
					RestartChangeStateInAir();
				}
			}
		}
	}


	UFUNCTION()
	void OnAnimFinished() {
		sprite->Play("normal_side_climbing_loop");
	}

	void RestartChangeStateInAir() {
		change_state_inair = false;
		wait_change_state = character->default_side_climbing_down_hold_time;
	}

	void ReverseDir() {
		if (character->sprite_dir == EDirection::LEFT) {
			ChangeSpriteDir(EDirection::RIGHT);
		}
		else {
			ChangeSpriteDir(EDirection::LEFT);
		}
	}

	virtual void InputJumpPressed() {
		ASParam param;
		param.Add("is_side_jump");
		state_machine->ChangeState("ActionStateJump", &param);
	}
};

