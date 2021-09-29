// Fill out your copyright notice in the Description page of Project Settings.


#include "TestGameModeBase.h"
#include "RollableWidget.h"
#include "Kismet/GameplayStatics.h"
#include "TestC/Items/ItemBase.h"
#include "Blueprint/UserWidget.h"

void ATestGameModeBase::BeginPlay()
{
	TArray<AActor*> Items;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AItemBase::StaticClass(), Items);
	ItemsInLevel = Items.Num();

	if (GameWidgetClass) {
		GameWidget = Cast<URollableWidget>(CreateWidget(GetWorld(), GameWidgetClass));

		if (GameWidget) {
			GameWidget->AddToViewport();
			UpdateItemText();
		}
	}
}

void ATestGameModeBase::UpdateItemText()
{
	GameWidget->SetItemText(ItemsCollected, ItemsInLevel);
}

void ATestGameModeBase::ItemCollected()
{
	ItemsCollected++;
	UpdateItemText();
}
