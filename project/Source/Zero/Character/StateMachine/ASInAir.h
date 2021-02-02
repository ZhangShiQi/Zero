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

	State state = RAISE;
	FVector last_velocity;

	virtual void OnEnter(const ASParam *param) {
		UActionStateMove::OnEnter(param);

		sprite->OnFinishedPlaying.AddDynamic(this, &UActionStateInAir::OnFinsihedPlaying);

		if (param && param->Find("is_jump")) {
			state = RAISE;
			sprite->Play("normal_raise_start");
			character->Jump();
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

		if (!is_on_ground) {
			if (state == RAISE && velocity.Z <= 0.f) {
				state = FLOW;
				sprite->Play("normal_flow_start");
			}
		}
		else {
			if (state == FLOW || state == RAISE) {
				state = LANDING;
				sprite->Play("normal_landing");
			}
		}

		last_velocity = velocity;
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
			if (fabs(move_axis) <= 0.01f) {
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


	virtual void InputMove(float axis) {
		UActionStateMove::InputMove(axis);
	}

	virtual void InputJumpReleased() {
		character->StopJumping();

	}

};
