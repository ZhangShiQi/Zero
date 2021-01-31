// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "FlipbookSet.generated.h"



class UPaperFlipbook;

/**
 * 
 */
UCLASS()
class ZERO_API UFlipbookSet : public UPrimaryDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
	FName name;

	UPROPERTY(EditAnywhere)
	TMap<FName, UPaperFlipbook *> set;

public:
	UPaperFlipbook *GetFlipbook(FName flipbook_name) {
		return set[flipbook_name];
	}

};
