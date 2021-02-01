// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterZero.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "Sprite/FlipbookSprite.h"
#include "StateMachine/StateInputName.h"
#include "StateMachine/ASIdle.h"
#include "StateMachine/ASMove.h"
#include "StateMachine/ASRun.h"
#include "StateMachine/ASInAir.h"

ACharacterZero::ACharacterZero(const FObjectInitializer &ObjectInitializer)
	:Super(ObjectInitializer.DoNotCreateDefaultSubobject(ACharacter::MeshComponentName))
{
	// set capsule component.
	UCapsuleComponent *capsule = GetCapsuleComponent();
	capsule->SetCapsuleRadius(10.0f);
	capsule->SetCapsuleHalfHeight(18.5f);

	// set movement component.
	UCharacterMovementComponent *movement = GetCharacterMovement();
	// move
	movement->MaxStepHeight = 8.0f;
	movement->MaxWalkSpeed = 180.0f;
	movement->MaxWalkSpeedCrouched = 120.0f;

	// jump
	movement->JumpZVelocity = 280.0f;
	movement->BrakingDecelerationFalling = 1000.0f;
	movement->AirControl = 1.0f;
	JumpMaxHoldTime = 0.2f;
	JumpMaxCount = 1;


	// flipbook_sprite.
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

	// register state input.
	state_machine->state_input->axis.add(GET_SIN(CharacterMove));


	// register state machine.
	state_machine->RegisterState(UActionStateIdle::StaticClass());
	state_machine->RegisterState(UActionStateRun::StaticClass());

	// first state.
	state_machine->ChangeState("ActionStateIdle");
}


void ACharacterZero::SetupPlayerInputComponent(UInputComponent *input)
{
	Super::SetupPlayerInputComponent(input);

	input->BindAxis(GET_SIN(CharacterMove), this, &ACharacterZero::InputMove);
}

void ACharacterZero::InputMove(float axis)
{
	if (state_machine->state_input) 
	{
		state_machine->state_input->InputAxis(GET_SIN(CharacterMove), axis);
	}
}
