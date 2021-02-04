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
	float last_max_walk_speed;
public:
	virtual void OnEnter(const ASParam *param) {
		UActionStateMove::OnEnter(param);
		sprite->OnFinishedPlaying.AddDynamic(this, &UActionStateRush::OnAnimFinished);

		sprite->Play("normal_rush_start");


		duration = 10.5f;
		last_max_walk_speed = movement->MaxWalkSpeed;

		movement->MaxWalkSpeed *= 2.0f;
		is_end = false;
	}

	virtual void OnExit() {
		UActionStateMove::OnExit();
		sprite->OnFinishedPlaying.RemoveDynamic(this, &UActionStateRush::OnAnimFinished);

		movement->MaxWalkSpeed = last_max_walk_speed;
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
		}
	}

	virtual void InputRushPressed() {

	}

	virtual void InputRushReleased() {
		if (is_end == false) {
			is_end = true;
			sprite->Play("normal_rush_end");
		}
	}

	virtual void InputMove(float axis) {
		// 
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

