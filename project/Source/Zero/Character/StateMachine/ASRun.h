// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ASMove.h"
#include "ASRun.generated.h"


UCLASS(Blueprinttype, Blueprintable)
class ZERO_API UActionStateRun : public UActionStateMove
{
	GENERATED_BODY()

public:
	virtual void OnEnter(const ASParam *param) {
		UActionStateMove::OnEnter(param);

		float start_pos_time = 0.f;

		if (param) {
			const FString *str_time = param->Find("start_play_time");
			if (str_time) {
				start_pos_time = FCString::Atof(**str_time);
			}
		}

		sprite->Play("normal_run", start_pos_time);
	}

	virtual void InputMove(float axis) {

		if (is_on_ground) {
			if (fabs(axis) <= 0.01f) {
				state_machine->ChangeState("ActionStateIdle");
			}
			else {
				UActionStateMove::InputMove(axis);
			}
		}
		else {
			state_machine->ChangeState("ActionStateInAir");
		}
	}
};

