// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayField.h"

#include "Runtime/Engine/Classes/Engine/World.h"


// Sets default values
APlayField::APlayField()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	this->BorderBlocks.Reserve((this->HEIGHT * 2) + this->WIDTH + 2);

	this->RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	this->Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	this->Camera->SetupAttachment(this->RootComponent);

	this->AutoPossessPlayer = EAutoReceiveInput::Player0;
}

// Called when the game starts or when spawned
void APlayField::BeginPlay()
{
	Super::BeginPlay();
	this->CreateBorder();

	this->Camera->SetRelativeLocation(FVector{ -2600.f, -(float)((this->WIDTH * ABlock::SIZE) / 2), (float)((this->HEIGHT * ABlock::SIZE) / 2) });
}

// Called every frame
void APlayField::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayField::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	if (PlayerInputComponent)
	{
		PlayerInputComponent->BindAction("ShiftDown", IE_Pressed, this, &APlayField::ShiftDown);
		PlayerInputComponent->BindAction("ShiftLeft", IE_Pressed, this, &APlayField::ShiftLeft);
		PlayerInputComponent->BindAction("ShiftRight", IE_Pressed, this, &APlayField::ShiftLeft);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No input component!"));
	}
}

void APlayField::CreateBorder()
{
	for (int i = -1; i < this->HEIGHT; ++i) 
	{
		this->BorderBlocks.Push(this->CreateCell({ -1.f, (float)i }));
		this->BorderBlocks.Push(this->CreateCell({ (float)this->WIDTH, (float)i }));
	}

	for (int i = 0; i < this->WIDTH; ++i) 
	{
		this->BorderBlocks.Push(this->CreateCell({ (float)i, -1.f }));
	}
}

void APlayField::ShiftDown()
{
	UE_LOG(LogTemp, Warning, TEXT("SHIFT DOWN"));
}

void APlayField::ShiftLeft()
{
	UE_LOG(LogTemp, Warning, TEXT("SHIFT LEFT"));
}

void APlayField::ShiftRight()
{
	UE_LOG(LogTemp, Warning, TEXT("SHIFT RIGHT"));
}

ABlock* APlayField::CreateCell(FVector2D FieldPosition)
{
	FVector FieldLocation = this->GetActorLocation();
	FVector SpawnLocation = FVector(FieldLocation);

	SpawnLocation.X += FieldPosition.X * ABlock::SIZE;
	SpawnLocation.Z += FieldPosition.Y * ABlock::SIZE;

	return this->GetWorld()->SpawnActor<ABlock>(SpawnLocation, FRotator::ZeroRotator);
}
