// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GameFramework/PawnMovementComponent.h"

#include "ActionStateMachine/ActionStateInput.h"
#include "ActionStateMachine/ActionState.h"

#include "Character/Sprite/FlipbookSprite.h"
#include "Character/CharacterZero.h"

#include "ASMove.generated.h"


UCLASS(Blueprinttype, Blueprintable)
class ZERO_API UActionStateMove : public UActionState
{
	GENERATED_BODY()

public:
	virtual void OnEnter(const ASParam *param) {
		state_input->axis["CharacterMove"].BindUObject(this, &UActionStateMove::InputMove);

		movement = ((ACharacterZero *)owner)->GetMovementComponent();
		sprite = ((ACharacterZero *)owner)->GetSprite();
	}

	virtual void OnExit() {
		state_input->axis["CharacterMove"].Unbind();

	}

	virtual void OnUpdate(float delta) {
		if (movement) {
			if (movement->IsMovingOnGround()) {
				UE_LOG(LogTemp, Log, TEXT("Is On Ground"));
			}
			else {
				UE_LOG(LogTemp, Log, TEXT("Not On Ground"));
			}
		}
	};
	//
	virtual void InputMove(float axis) {
		move_axis = axis;

		if (movement) {
			movement->AddInputVector(FVector(move_axis, 0, 0), false);

			if (move_axis < -0.01f) {
				sprite->SetWorldScale3D(FVector::OneVector);
			}
			else if (move_axis > 0.01f) {
				sprite->SetWorldScale3D(FVector(-1, 1, 1));
			}
		}
	}

	virtual void InputJumpPressed() {

	}

	virtual void InputJumpReleased() {

	}

protected:
	UPawnMovementComponent *movement;
	UFlipbookSprite *sprite;

	float move_axis;
};

