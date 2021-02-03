// Fill out your copyright notice in the Description page of Project Settings.


#include "SideDetectBox.h"

USideDetectBox::USideDetectBox(const FObjectInitializer &ObjectInitializer)
	:Super(ObjectInitializer)
{

}

void USideDetectBox::BeginPlay()
{
	UBoxComponent::BeginPlay();

	hit_count = 0;

	OnComponentBeginOverlap.AddDynamic(this, &USideDetectBox::OnBeginOverlap);
	OnComponentEndOverlap.AddDynamic(this, &USideDetectBox::OnEndOverlap);
}

void USideDetectBox::OnBeginOverlap(UPrimitiveComponent *OverlappedComponent,
	AActor *OtherActor,
	UPrimitiveComponent *OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult &SweepResult)
{
	hit_count++;
	UE_LOG(LogTemp, Log, TEXT("BeginOverlap HitCount:%d"), hit_count);
}

void USideDetectBox::OnEndOverlap(UPrimitiveComponent *OverlappedComponent,
	AActor *OtherActor,
	UPrimitiveComponent *OtherComp,
	int32 OtherBodyIndex)
{
	hit_count--;
	UE_LOG(LogTemp, Log, TEXT("EndOverlap HitCount:%d"), hit_count);
}

