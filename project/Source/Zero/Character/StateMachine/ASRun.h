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

		sprite->Play("normal_run");
	}

	virtual void InputMove(float axis) {
		if (fabs(axis) <= 0.01f) {
			state_machine->ChangeState("ActionStateIdle");
		}
		else {
			UActionStateMove::InputMove(axis);
		}
	}
};

