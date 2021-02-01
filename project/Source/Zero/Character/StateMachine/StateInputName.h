
#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

enum eSIN {
	SIN_CharacterMove = 0,


	SIN_MAX,
};

extern FName __SIN[SIN_MAX];

#define GET_SIN(n) __SIN[SIN_##n]

