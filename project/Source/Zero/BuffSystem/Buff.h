// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Buff.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, BlueprintAble)
class ZERO_API UBuff : public UObject
{
	GENERATED_BODY()

public:

	virtual void OnInit();
	virtual void OnUpdate(float delta);
	virtual void OnExit();


public:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	UBuff *prev;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	UBuff *next;


	UPROPERTY(BlueprintReadWrite)
	int id;

	UPROPERTY(BlueprintReadWrite)
	int type;

	UPROPERTY(BlueprintReadWrite)
	float duration;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	bool is_inited = false;
};
