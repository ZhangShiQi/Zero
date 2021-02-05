// Fill out your copyright notice in the Description page of Project Settings.


#include "BuffManager.h"
#include "Buff.h"

// Sets default values for this component's properties
UBuffManager::UBuffManager()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	head = tail = nullptr;

	is_pause = false;
}


// Called when the game starts
void UBuffManager::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UBuffManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);


	if (!is_pause) {
		UBuff *buff = head;
		while (buff) {
			if (buff->is_inited) {
				buff->OnUpdate(DeltaTime);

				buff->duration -= DeltaTime;
				if (buff->duration <= 0.f) {
					buff->OnExit();

					UBuff *tmp = buff;
					buff = buff->next;

					RemoveBuff(tmp);
					continue;
				}
			}
			else {
				buff->OnInit();
				buff->is_inited = true;
			}


			buff = buff->next;
		}
	}
	
}


bool UBuffManager::AppendBuff(UBuff *buff)
{
	if (buff == nullptr) {
		return false;
	}

	if (tail == nullptr) {
		head = tail = buff;
		buff->prev = nullptr;
		buff->next = nullptr;
	}
	else {
		tail->next = buff;
		buff->prev = tail;
		buff->next = nullptr;

		tail = buff;
	}

	return true;
}

bool UBuffManager::RemoveBuff(UBuff *buff, bool mark_pending_kill)
{
	if (buff == nullptr) {
		return false;
	}

	if (buff == head && buff == tail) {
		head = tail = nullptr;
	}
	else {
		if (buff == head) {
			buff->next->prev = nullptr;
			head = buff->next;
		}
		else if (buff == tail) {
			buff->prev->next = nullptr;
			tail = buff->prev;
		}
		else {
			buff->prev->next = buff->next;
			buff->next->prev = buff->prev;
		}
	}

	if (mark_pending_kill) {
		buff->MarkPendingKill();
	}

	return true;
}


