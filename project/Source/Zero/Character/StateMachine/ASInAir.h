// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "ASMove.h"
#include "ASInAir.generated.h"


UCLASS(Blueprinttype, Blueprintable)
class ZERO_API UActionStateInAir : public UActionStateMove
{
	GENERATED_BODY()
public:

	enum State {
		RAISE,
		FLOW,
		LANDING
	};

	bool is_jump = false;
	State state = RAISE;
	FVector last_velocity;

	float disable_input_move = 0.f;

	virtual void OnEnter(const ASParam *param) {
		UActionStateMove::OnEnter(param);

		sprite->OnFinishedPlaying.AddDynamic(this, &UActionStateInAir::OnFinsihedPlaying);

		is_jump = false;
		if (param && param->Find("is_jump")) {
			state = RAISE;

			if (param->Find("is_side_jump")) {
				disable_input_move = 0.1f;
				sprite->Play("normal_side_climbing_jump");
			}
			else {
				sprite->Play("normal_raise_start");
			}

			character->Jump();
			is_jump = true;
		}
		//else if (param && param->Find("need_acceleration") {
		//	Enable_Acceleration();
		//}
		else {
			state = FLOW;
			sprite->Play("normal_flow_start");
		}
	}

	virtual void OnExit() {
		UActionStateMove::OnExit();

		sprite->OnFinishedPlaying.RemoveDynamic(this, &UActionStateInAir::OnFinsihedPlaying);
	}

	virtual void OnUpdate(float delta) {
		UActionStateMove::OnUpdate(delta);
		disable_input_move -= delta;

		if (!character->is_on_ground) {
			if (state == RAISE && movement->Velocity.Z <= 0.f) {
				state = FLOW;
				sprite->Play("normal_flow_start");
			}

			// detect side wall.
			if (side_box->IsHit()) {
				if (movement->Velocity.Z <= 0.f) {
					state_machine->ChangeState("ActionStateSideClimbing");
				}


			}
		}
		else {
			if (state == FLOW || state == RAISE) {
				state = LANDING;

				if (IsInputMove()) { // 如果有左右移动,直接进入run状态.
					ASParam param;
					param.Add("start_play_time", "0.5");

					state_machine->ChangeState("ActionStateRun", &param);
				}
				else {
					sprite->Play("normal_landing");
				}
			}
		}

		last_velocity = movement->Velocity;
	}

	UFUNCTION()
		virtual void OnFinsihedPlaying()
	{
		switch (state) {
		case RAISE:
			sprite->Play("normal_raise_loop");
			break;

		case FLOW:
			sprite->Play("normal_flow_loop");
			break;

		case LANDING:
			if (!IsInputMove()) {
				state_machine->ChangeState("ActionStateIdle");
			}
			else {
				ASParam param;
				param.Add("start_play_time", "0.55");

				state_machine->ChangeState("ActionStateRun", &param);
			}

			break;
		}
	}

	
	virtual void InputJumpPressed() {
		if (side_box->IsHit()) {
			ASParam param;
			param.Add("is_side_jump");
			state_machine->ChangeState("ActionStateJump", &param);
		}
		else {
			UActionStateMove::InputJumpPressed();
		}
	}

	virtual void InputJumpReleased() {
		if (is_jump) {
			character->StopJumping();
		}
	}

};
