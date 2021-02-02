// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "FlipbookSet.generated.h"



class UPaperFlipbook;

USTRUCT(BlueprintType)
struct FPaperFlipbookData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	UPaperFlipbook *flipbook;

	UPROPERTY(EditAnywhere)
	bool is_looping;
};

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
	TMap<FName, FPaperFlipbookData> set;

public:

	FPaperFlipbookData *GetFlipbookData(FName flipbook_name) {
		FPaperFlipbookData *result = set.Find(flipbook_name);
		return result;
	}

	UPaperFlipbook *GetFlipbook(FName flipbook_name) {
		FPaperFlipbookData *result = set.Find(flipbook_name);
		if (result == nullptr) {
			return nullptr;
		}

		return result->flipbook;
	}

	bool GetFlipbookLooping(FName flipbook_name) {
		FPaperFlipbookData *result = set.Find(flipbook_name);
		if (result == nullptr) {
			return nullptr;
		}

		return result->is_looping;
	}

};
