// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorTest.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

// Sets default values
AActorTest::AActorTest()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");

	RootComponent = Mesh;
	SpringArm->SetupAttachment(Mesh); 
	Camera->SetupAttachment(SpringArm);

	Mesh->SetSimulatePhysics(true);
	Mesh->OnComponentHit.AddDynamic(this, &AActorTest::OnHit);
}

// Called when the game starts or when spawned
void AActorTest::BeginPlay()
{
	Super::BeginPlay();
	
	MoveForce *= Mesh->GetMass();
	JumpImpulse *= Mesh->GetMass();
}

// Called every frame
void AActorTest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AActorTest::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//Axis Bindings
	InputComponent->BindAxis("MoveForward", this, &AActorTest::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &AActorTest::MoveRight);
	//Action Bindings
	InputComponent->BindAction("Jump", IE_Pressed, this, &AActorTest::Jump);
}

void AActorTest::MoveRight(float value)
{
	const FVector Right = Camera->GetRightVector() * MoveForce * value;
	Mesh->AddForce(Right);
}

void AActorTest::MoveForward(float value)
{
	const FVector Forward = Camera->GetForwardVector() * MoveForce * value;
	Mesh->AddForce(Forward);
}

void AActorTest::Jump()
{
	if (JumpCount >= MaxJumpCount)
		return;

	Mesh->AddImpulse(FVector(0, 0, JumpImpulse));
	JumpCount++;
}

void AActorTest::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	float hitDirection = Hit.Normal.Z;
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Orange, FString::Printf(TEXT("Z Normal: %f"), hitDirection));

	if (hitDirection > 0)
		JumpCount = 0;
}