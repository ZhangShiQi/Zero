// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterZero.h"
#include "FlipbookSprite.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "ActionState.h"

ACharacterZero::ACharacterZero(const FObjectInitializer &ObjectInitializer)
	:Super(ObjectInitializer.DoNotCreateDefaultSubobject(ACharacter::MeshComponentName))
{
	flipbook_sprite = CreateDefaultSubobject<UFlipbookSprite>("FlipbookSprite0");
	flipbook_sprite->AlwaysLoadOnClient = true;
	flipbook_sprite->AlwaysLoadOnServer = true;
	flipbook_sprite->bOwnerNoSee = false;
	flipbook_sprite->bAffectDynamicIndirectLighting = true;
	flipbook_sprite->PrimaryComponentTick.TickGroup = TG_PrePhysics;
	flipbook_sprite->SetupAttachment(GetCapsuleComponent());
	static FName CollisionProfileName(TEXT("CharacterMesh"));
	flipbook_sprite->SetCollisionProfileName(CollisionProfileName);
	flipbook_sprite->SetGenerateOverlapEvents(false);

	// action state machine.
	state_machine = CreateDefaultSubobject<UActionStateMachine>("ActionStateMachine", false);
}


void ACharacterZero::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if (!IsPendingKill())
	{
		if (flipbook_sprite)
		{
			// force animation tick after movement component updates
			if (flipbook_sprite->PrimaryComponentTick.bCanEverTick && GetCharacterMovement())
			{
				flipbook_sprite->PrimaryComponentTick.AddPrerequisite(GetCharacterMovement(), GetCharacterMovement()->PrimaryComponentTick);
			}
		}
	}
}


void ACharacterZero::BeginPlay()
{
	Super::BeginPlay();

	state_machine->RegisterState(UActionStateIdle::StaticClass());
	state_machine->RegisterState(UActionStateRun::StaticClass());

	// first state.
	state_machine->ChangeState("ActionStateIdle");
}


void ACharacterZero::SetupPlayerInputComponent(UInputComponent *input)
{
	Super::SetupPlayerInputComponent(input);

	//input->BindAxis("CharacterMove", this, &ACharacterZero::InputMove);
	input->BindAxis("CharacterMove", state_machine->state_input, &UActionStateInput::InputMove);

}

void ACharacterZero::InputMove(float axis)
{
	if (state_machine->state_input) 
	{
		//state_machine->state_input->InputMove(axis);
		state_machine->state_input->InputMove(axis);
	}
}
