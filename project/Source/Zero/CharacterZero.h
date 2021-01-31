
#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "ActionStateMachine.h"
#include "CharacterZero.generated.h"







/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class ZERO_API ACharacterZero : public APaperCharacter
{
	GENERATED_BODY()
	
public:
	ACharacterZero();
	virtual ~ACharacterZero();

public:




protected:
	UActionStateMachine *state_machine;

};
