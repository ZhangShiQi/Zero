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
	TMap<FName, T> delegate_input;

	T &get(const FName &name) {
		return delegate_input[name];
	}

	void add(const FName &name) {
		delegate_input.Add(name, T());
	}

	T &operator[] (const FName &name) {
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
	void InputAxis(const FName &name, float axis);
	void InputActionPressed(const FName &name);
	void InputActionReleased(const FName &name);
};
