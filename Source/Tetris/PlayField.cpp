// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayField.h"

#include "Runtime/Engine/Classes/Engine/World.h"


// Sets default values
APlayField::APlayField()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	this->Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
}

// Called when the game starts or when spawned
void APlayField::BeginPlay()
{
	Super::BeginPlay();
	this->CreateBorder();
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
	
}

void APlayField::CreateBorder()
{
	// Two blocks for each row, one block for each column, one block for each bottom corner
	int totalBorderBlocks = (this->HEIGHT * 2) + this->WIDTH + 2;
	int blockCounter = 0;

	UE_LOG(LogTemp, Warning, TEXT("Reserved space for blocks: %i"), totalBorderBlocks);

	this->BorderBlocks.Reserve(totalBorderBlocks);

	for (int i = -1; i < this->HEIGHT; ++i) 
	{
		this->BorderBlocks.Push(this->CreateCell({ -1.f, (float)i }));
		this->BorderBlocks.Push(this->CreateCell({ (float)this->WIDTH, (float)i }));

		blockCounter += 2;
	}

	for (int i = 0; i < this->WIDTH; ++i) 
	{
		this->BorderBlocks.Push(this->CreateCell({ (float)i, -1.f }));
		++blockCounter;
	}

	UE_LOG(LogTemp, Warning, TEXT("Created blocks: %i"), blockCounter);
}

ABlock* APlayField::CreateCell(FVector2D FieldPosition)
{
	FVector FieldLocation = this->GetActorLocation();
	FVector SpawnLocation = FVector(FieldLocation);

	SpawnLocation.X += FieldPosition.X * ABlock::SIZE;
	SpawnLocation.Z += FieldPosition.Y * ABlock::SIZE;

	return this->GetWorld()->SpawnActor<ABlock>(SpawnLocation, FRotator::ZeroRotator);
}
