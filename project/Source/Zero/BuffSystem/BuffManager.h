// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BuffManager.generated.h"

class UBuff;


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ZERO_API UBuffManager : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBuffManager();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	bool AppendBuff(UBuff *buff);
	bool RemoveBuff(UBuff *buff, bool mark_pending_kill = true);

public:
	UPROPERTY(BlueprintReadWrite)
	bool is_pause;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	UBuff *head;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	UBuff *tail;
		
};
