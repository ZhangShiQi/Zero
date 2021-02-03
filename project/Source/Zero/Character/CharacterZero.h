
#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "ActionStateMachine/ActionStateMachine.h"

#include "CharacterZero.generated.h"


class UFlipbookSprite;
class USideDetectBox;

UENUM(BlueprintType)
enum class EDirection:uint8 {
	NONE = 0,
	RIGHT,
	LEFT,
};

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class ZERO_API ACharacterZero : public ACharacter
{
	//GENERATED_BODY()
	GENERATED_UCLASS_BODY()
	
public:

	void BeginPlay();

public:


	void InputMove(float axis);
	void InputJumpPressed();
	void InputJumpReleased();

	virtual void SetupPlayerInputComponent(class UInputComponent *input);
	virtual void PostInitializeComponents();

	/** Returns Sprite subobject **/
	FORCEINLINE UFlipbookSprite *GetSprite() const { return flipbook_sprite; }
	FORCEINLINE USideDetectBox *GetSideBox() const { return side_box; }

public:
	// default value.
	UPROPERTY(EditAnywhere)
	float default_side_climbing_speed = -10.f;

	UPROPERTY(EditAnywhere)
	FVector default_side_jump_velocity = FVector(300.0f, 0.f, 250.0f);

	UPROPERTY(EditAnywhere)
	float default_side_climbing_down_hold_time = 0.2f;

public:
	// temp variable.
	UPROPERTY(BlueprintReadonly, VisibleAnywhere)
	bool is_on_ground;
	
	UPROPERTY(BlueprintReadonly, VisibleAnywhere)
	EDirection sprite_dir;

protected:
	UPROPERTY(Category = StateMachine, VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UActionStateMachine *state_machine;

	//UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	//UFlipbookSprite *Sprite;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UFlipbookSprite *flipbook_sprite;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	USideDetectBox *side_box;
};
