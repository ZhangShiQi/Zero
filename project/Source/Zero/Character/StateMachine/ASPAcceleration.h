// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ActionStateMachine/ActionState.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Character/CharacterZero.h"
#include "ASPAcceleration.generated.h"


UCLASS(Blueprinttype, Blueprintable)
class ZERO_API UActionStateAcceleration: public UActionState
{
	GENERATED_BODY()

public:
	ACharacterZero *character;
	UCharacterMovementComponent *movement;

	float duration = 0;
	float last_max_walk_speed;

	bool check_is_on_ground = false;
public:
	virtual void OnEnter(const ASParam *param) {
		character = dynamic_cast<ACharacterZero *>(owner);
		movement = dynamic_cast<UCharacterMovementComponent *>(character->GetMovementComponent());

		check_is_on_ground = false;

		if (param && param->Find("duration")) {
			FString str_value = *param->Find("duration");
			duration = FCString::Atof(*str_value);
		}
		else {
			duration = character->default_rush_duration;
		}

		last_max_walk_speed = movement->MaxWalkSpeed;
		movement->MaxWalkSpeed *= character->default_rush_acceleration_scale;
	}

	virtual void OnExit() {
		movement->MaxWalkSpeed = last_max_walk_speed;
	}

	virtual void OnUpdate(float delta) {
		duration -= delta;

		if (check_is_on_ground && character->is_on_ground) {
			state_machine->ClearParallelState();
			return;
		}
		else {
			if (character->is_on_ground == false) {
				check_is_on_ground = true;
			}
		}

		if (duration <= 0.f && character->is_on_ground) {
			state_machine->ClearParallelState();
		}

		GEngine->AddOnScreenDebugMessage(2, 0, FColor::White,
			FString::Printf(TEXT("ASPAcceleration duration:%f"), duration));
	}


};

