// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "SideDetectBox.generated.h"

/**
 * 
 */
//UCLASS(BlueprintType, BlueprintAble)
UCLASS(ClassGroup = "Collision", hidecategories = (Object, LOD, Lighting, TextureStreaming), editinlinenew, meta = (DisplayName = "Side Detect Box", BlueprintSpawnableComponent))
class ZERO_API USideDetectBox : public UBoxComponent
{
	GENERATED_UCLASS_BODY()
public:

	virtual void BeginPlay();

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent *OverlappedComponent,
		AActor *OtherActor,
		UPrimitiveComponent *OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult &SweepResult);

	UFUNCTION()
	void OnEndOverlap(UPrimitiveComponent *OverlappedComponent,
		AActor *OtherActor,
		UPrimitiveComponent *OtherComp,
		int32 OtherBodyIndex);


	FORCEINLINE
	bool IsHit() const { return hit_count > 0; }

public:
	int hit_count;

};
