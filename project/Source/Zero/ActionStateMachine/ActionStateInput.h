// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ActionStateInput.generated.h"


DECLARE_DELEGATE_OneParam(FActionStateInputAxis, float);
DECLARE_DELEGATE(FActionStateInputAction);


template <class T>
class ActionStateInputDelegate {
public:
	// axis.
	TArray<T> delegate_input;

	void init(int max_name) {
		delegate_input.Reserve(max_name);
		for (int i = 0; i < max_name; i++) {
			delegate_input.Add(T());
		}
	}

	T &get(int name) {
		return delegate_input[name];
	}

	T &operator[] (int name) {
		return get(name);
	}
};

/**
 * 
 */
UCLASS(Blueprinttype, Blueprintable)
class ZERO_API UActionStateInput : public UObject
{
	GENERATED_BODY()
	
public:
	UActionStateInput();
	virtual ~UActionStateInput();

	// axis.
	ActionStateInputDelegate<FActionStateInputAxis>		axis;
	ActionStateInputDelegate<FActionStateInputAction>	pressed;
	ActionStateInputDelegate<FActionStateInputAction>	released;

public:

	void Init(int max_input_name);

	void InputAxis(int name, float axis);
	void InputActionPressed(int name);
	void InputActionReleased(int name);
};
