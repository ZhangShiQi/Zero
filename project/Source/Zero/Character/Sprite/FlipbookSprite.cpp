//
//
//


#include "FlipbookSprite.h"
#include "FlipbookSet.h"

void UFlipbookSprite::Play(const FName &name, float play_position)
{
	if (flipbook_set == nullptr) {
		UE_LOG(LogTemp, Error, TEXT("No flipbook set. %s"), *name.ToString());
		return;
	}

	FPaperFlipbookData *flipbook_data = flipbook_set->GetFlipbookData(name);
	if (flipbook_data == nullptr) {
		UE_LOG(LogTemp, Error, TEXT("Invalid flipbook %s"), *name.ToString());
		return;
	}

	SetFlipbook(flipbook_data->flipbook);
	SetLooping(flipbook_data->is_looping);

	SetPlaybackPosition(play_position, false);

	UPaperFlipbookComponent::Play();
}



