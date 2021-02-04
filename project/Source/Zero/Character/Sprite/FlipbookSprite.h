// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperFlipbookComponent.h"
#include "FlipbookSprite.generated.h"

/**
 * 
 */
UCLASS(ShowCategories = (Mobility, ComponentReplication), ClassGroup = ZeroFlipbook, meta = (BlueprintSpawnableComponent))
class ZERO_API UFlipbookSprite : public UPaperFlipbookComponent
{
	GENERATED_BODY()
	
public:
	void Play(const FName &name, float play_position = 0.0f);


	FORCEINLINE FName GetCurrentPlaying() const { return current_playing; }

public:
	UPROPERTY(EditAnywhere)
		class UFlipbookSet *flipbook_set;


	UPROPERTY(VisibleAnywhere, BlueprintReadonly)
		FName current_playing;

};
