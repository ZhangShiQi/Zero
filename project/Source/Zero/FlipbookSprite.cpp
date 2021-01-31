// Fill out your copyright notice in the Description page of Project Settings.


#include "FlipbookSprite.h"
#include "FlipbookSet.h"

void UFlipbookSprite::Play(const FName &name)
{
	if (flipbook_set == nullptr) {
		UE_LOG(LogTemp, Error, TEXT("No flipbook set. %s"), *name.ToString());
		return;
	}

	UPaperFlipbook *flipbook = flipbook_set->GetFlipbook(name);
	if (flipbook == nullptr) {
		UE_LOG(LogTemp, Error, TEXT("Invalid flipbook %s"), *name.ToString());
		return;
	}

	SetFlipbook(flipbook);
	PlayFromStart();
}


