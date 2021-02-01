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

	virtual void InputMove(float axis) {
		if (fabs(axis) > 0.01f) {
			state_machine->ChangeState("ActionStateRun");
		}
	}

};
