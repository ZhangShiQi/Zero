// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionStateMachine.h"
#include "ActionState.h"

// Sets default values for this component's properties
UActionStateMachine::UActionStateMachine()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	

	state_input = CreateDefaultSubobject<UActionStateInput>("StateInput", false);
}

// Called when the game starts
void UActionStateMachine::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void UActionStateMachine::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (current_state) {
		current_state->OnUpdate(DeltaTime);
	}
}

void UActionStateMachine::RegisterAllStates()
{
	/*for (int i = 0; i < STATE_NAME_NUM(); i++) {
		const TCHAR *class_name = STATE_NAME_ARRAY()[i];

		UClass *u_class = FindObject<UClass>(ANY_PACKAGE, class_name);
		if (u_class) {
			RegisterState(u_class);
		}
	}*/
}

bool UActionStateMachine::RegisterState(const char *state_class_name)
{
	UClass *u_class = FindObject <UClass>(ANY_PACKAGE, ANSI_TO_TCHAR(state_class_name));
	if (u_class == nullptr) {
		return false;
	}

	TSubclassOf<UActionState> state_class(u_class);
	RegisterState(*state_class);
	return true;
}

void UActionStateMachine::RegisterState(TSubclassOf<UActionState> state_class)
{
	UActionState *new_state = NewObject<UActionState>(this, state_class);

	FName class_name = state_class->GetFName();
	UE_LOG(LogTemp, Log, TEXT("register state:%s") , *class_name.ToString());

	state_map.Add(class_name, new_state);
	
	new_state->state_machine = this;
	new_state->state_input = state_input;

	new_state->owner = GetOwner();
}

bool UActionStateMachine::ChangeState(FName state_class_name, TMap<FName, FString> *enter_param)
{
	UActionState *state = state_map[state_class_name];
	if (state == nullptr) {
		UE_LOG(LogTemp, Log, TEXT("Invalid state name %s"), *state_class_name.ToString());
		return false;
	}

	if (current_state) {
		current_state->OnExit();
	}

	current_state = state;
	current_state->OnEnter(enter_param);
	UE_LOG(LogTemp, Log, TEXT("Current state:%s"), *state_class_name.ToString());
	return true;
}


