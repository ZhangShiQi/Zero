// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ASMove.h"
#include "ASRush.generated.h"


UCLASS(Blueprinttype, Blueprintable)
class ZERO_API UActionStateRush: public UActionStateMove
{
	GENERATED_BODY()

public:
	bool is_end = false;
	float duration = 0;
	bool is_rush_start_finished = false;
public:
	void LaunchAcceleration() {
		ASParam param;
		param.Add("duration", FString::SanitizeFloat(duration));

		state_machine->SetParallelState("ActionStateAcceleration", &param);
	}

	void StopAcceleration() {
		state_machine->ClearParallelState();
	}

	virtual void OnEnter(const ASParam *param) {
		UActionStateMove::OnEnter(param);
		sprite->OnFinishedPlaying.AddDynamic(this, &UActionStateRush::OnAnimFinished);

		sprite->Play("normal_rush_start");
		is_rush_start_finished = false; 

		duration = character->default_rush_duration;
		is_end = false;

		LaunchAcceleration();
	}

	virtual void OnExit() {
		UActionStateMove::OnExit();
		sprite->OnFinishedPlaying.RemoveDynamic(this, &UActionStateRush::OnAnimFinished);
	}

	virtual void OnUpdate(float delta) {
		UActionStateMove::OnUpdate(delta);

		duration -= delta;

		if (duration <= 0.f && is_end == false) {
			is_end = true;
			sprite->Play("normal_rush_end");
		}
	}


	UFUNCTION()
	void OnAnimFinished() {

		if (is_end) {
			state_machine->ChangeState("ActionStateIdle");
		}
		else {
			if (duration > 0.f) {
				sprite->Play("normal_rush_loop");
			}

			is_rush_start_finished = true;
		}
	}

	virtual void InputRushPressed() {

	}

	virtual void InputRushReleased() {
		if (is_end == false) {
			is_end = true;
			sprite->Play("normal_rush_end");
			StopAcceleration();
		}
	}

	virtual void InputMove(float axis) {
		
		if (character->default_change_dir_break_rush) {
			if (character->is_on_ground && is_rush_start_finished &&
				(axis > 0.1f && move_axis < -0.1f ||
					axis < -0.1f && move_axis > 0.1f)) {
				InputRushReleased();
			}
		}

		if (fabs(axis) <= 0.01f) {
			if (character->sprite_dir == EDirection::LEFT) {
				axis = -1.f;
			}
			else {
				axis = 1.f;
			}
		}

		UActionStateMove::InputMove(axis);
	}


};

