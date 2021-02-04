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

	virtual void OnEnter(const ASParam *param) {
		UActionStateMove::OnEnter(param);

		sprite->OnFinishedPlaying.AddDynamic(this, &UActionStateInAir::OnFinsihedPlaying);

		is_jump = false;
		if (param && param->Find("is_jump")) {
			state = RAISE;

			if (param->Find("is_side_jump")) {
				sprite->Play("normal_side_climbing_jump");
			}
			else {
				sprite->Play("normal_raise_start");
			}

			character->Jump();
			is_jump = true;
		}
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

		if (!character->is_on_ground) {
			if (state == RAISE && movement->Velocity.Z <= 0.f) {
				state = FLOW;
				sprite->Play("normal_flow_start");
			}

			// detect side wall.
			if (side_box->IsHit() && movement->Velocity.Z <= 0.f) {
				state_machine->ChangeState("ActionStateSideClimbing");
			}
		}
		else {
			if (state == FLOW || state == RAISE) {
				state = LANDING;

				if (IsInputMove()) {
					ASParam param;
					param.Add("start_play_time", "0.5f");

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

	virtual void InputJumpReleased() {
		if (is_jump) {
			character->StopJumping();
		}
	}

};
