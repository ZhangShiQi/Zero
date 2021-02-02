
#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "ActionStateMachine/ActionStateMachine.h"

#include "CharacterZero.generated.h"


class UFlipbookSprite;


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

protected:
	UPROPERTY(Category = StateMachine, VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UActionStateMachine *state_machine;

	//UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	//UFlipbookSprite *Sprite;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UFlipbookSprite *flipbook_sprite;

};
