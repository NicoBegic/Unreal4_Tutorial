// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemBase.h"
#include "TestC/Public/ActorTest.h"
#include "TestC/Public/TestGameModeBase.h"

// Sets default values
AItemBase::AItemBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	RootComponent = Mesh;

	Mesh->OnComponentBeginOverlap.AddDynamic(this, &AItemBase::OverlapBegin);
}

// Called when the game starts or when spawned
void AItemBase::BeginPlay()
{
	Super::BeginPlay();
}

void AItemBase::OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Cast<AActorTest>(OtherActor) != nullptr) {
		Collected();
	}
}

void AItemBase::Collected_Implementation()
{
	ATestGameModeBase* GameMode = Cast<ATestGameModeBase>(GetWorld()->GetAuthGameMode());

	if (GameMode) {
		GameMode->ItemCollected();
	}
}

