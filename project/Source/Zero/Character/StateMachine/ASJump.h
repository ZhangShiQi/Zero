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

		state_machine->ChangeState("ActionStateInAir", &ap);
	}
};

