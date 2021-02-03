// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ASMove.h"
#include "ASIdle.generated.h"


UCLASS(Blueprinttype, Blueprintable)
class ZERO_API UActionStateIdle : public UActionStateMove
{
	GENERATED_BODY()

public:
	virtual void OnEnter(const ASParam *param) {
		UActionStateMove::OnEnter(param);

		sprite->Play("normal_idle");
	}

	virtual void OnUpdate(float delta) {
		UActionStateMove::OnUpdate(delta);
		if (!character->is_on_ground) {
			state_machine->ChangeState("ActionStateInAir");
		}
	}

	virtual void InputMove(float axis) {
		UActionStateMove::InputMove(axis);

		if (IsInputMove()) {
			state_machine->ChangeState("ActionStateRun");
		}
	}

};
