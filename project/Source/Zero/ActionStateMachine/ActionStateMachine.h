// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ActionStateInput.h"
#include "ActionStateMachine.generated.h"


class UActionState;

UCLASS(BlueprintType, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ZERO_API UActionStateMachine : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UActionStateMachine();


protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


	void RegisterAllStates();

	bool RegisterState(const char *state_class_name);
	void RegisterState(TSubclassOf<UActionState> state_class);
	bool ChangeState(FName state_class_name, TMap<FName, FString> *enter_param = nullptr);


	void ClearParallelState();
	bool SetParallelState(FName state_class_name, TMap < FName, FString> *enter_param = nullptr);

public:
	static FName NoneStateName;


	UPROPERTY(BlueprintReadOnly)
	UActionStateInput *state_input;

	UPROPERTY(BlueprintReadOnly)
	UActionState *current_state;

	UPROPERTY(BlueprintReadOnly)
	UActionState *parallel_state;

	UPROPERTY()
	TMap<FName, UActionState *> state_map;
};
