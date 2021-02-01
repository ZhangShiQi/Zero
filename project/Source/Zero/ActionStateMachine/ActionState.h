// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ActionState.generated.h"


typedef TMap<FName, FString> ASParam;

class UActionStateMachine;
class UActionStateInput;

/**
 * 
 */
UCLASS(Blueprinttype, Blueprintable)
class ZERO_API UActionState : public UObject
{
	GENERATED_BODY()

public:

	virtual void OnUpdate(float delta) {}

	virtual void OnEnter(const ASParam *param) {}
	virtual void OnExit() {}

public:
	const FName &GetStateName() const { return state_name; }

protected:
	friend class UActionStateMachine;

	AActor *owner;

	FName state_name;
	UActionStateMachine *state_machine;
	UActionStateInput *state_input;
};
