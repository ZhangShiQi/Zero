
#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

enum eSIN {
	SIN_Move = 0,
	SIN_Jump,
	SIN_Rush,

	SIN_MAX,
};

extern FName __SIN[SIN_MAX];

#define GET_SIN(n) __SIN[SIN_##n]

