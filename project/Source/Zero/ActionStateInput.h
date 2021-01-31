// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ActionStateInput.generated.h"


DECLARE_DELEGATE_OneParam(FActionStateInputAxis, float);

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


	FActionStateInputAxis delegate_input_move;

public:
	void InputMove(float axis);





};
