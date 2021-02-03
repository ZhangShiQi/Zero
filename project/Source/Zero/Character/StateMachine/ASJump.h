// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ASMove.h"
#include "ASJump.generated.h"


UCLASS(Blueprinttype, Blueprintable)
class ZERO_API UActionStateJump : public UActionStateMove {
	GENERATED_BODY()
public:
	virtual void OnEnter(const ASParam *param) {
		UActionStateMove::OnEnter(param);
		
		ASParam ap;
		ap.Add("is_jump");
		if (param && param->Find("is_side_jump")) {
			ap.Add("is_side_jump");

			// fix movment velocity.
			movement->Velocity.Z = character->default_side_jump_velocity.Z;
			if (character->sprite_dir == EDirection::RIGHT) {
				movement->Velocity.X = -character->default_side_jump_velocity.X;
			}
			else {
				movement->Velocity.X = character->default_side_jump_velocity.X;
			}
		}

		state_machine->ChangeState("ActionStateInAir", &ap);
	}
};

