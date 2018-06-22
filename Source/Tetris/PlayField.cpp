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

	this->Camera->SetRelativeLocation(FVector{ -2600.f, (float)((this->WIDTH * ABlock::SIZE) / 2), (float)((this->HEIGHT * ABlock::SIZE) / 2) });
	this->SpawnNewTetromino((ETetrominoShape)0xFF);
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
		PlayerInputComponent->BindAction("ShiftRight", IE_Pressed, this, &APlayField::ShiftRight);
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
		this->BorderBlocks.Push(this->CreateBlock({ -1.f, (float)i }));
		this->BorderBlocks.Push(this->CreateBlock({ (float)this->WIDTH, (float)i }));
	}

	for (int i = 0; i < this->WIDTH; ++i) 
	{
		this->BorderBlocks.Push(this->CreateBlock({ (float)i, -1.f }));
	}
}

void APlayField::SpawnNewTetromino(ETetrominoShape Shape)
{
	FVector SpawnLocation = this->GetFieldPositionLocation({ FMath::DivideAndRoundDown((float)this->WIDTH, 2.f), (float)this->HEIGHT });

	this->ActiveTetromino = this->GetWorld()->SpawnActor<ATetromino>(SpawnLocation, FRotator::ZeroRotator);
	
	if ((uint8)Shape == 0xFF)
	{
		Shape = this->PickRandomShape();
	}

	this->ActiveTetromino->GenerateShape(Shape);

	this->Shift({ -(float)FMath::DivideAndRoundDown(this->ActiveTetromino->GetDimensions().X, 2), 0 });
}

ETetrominoShape APlayField::PickRandomShape()
{
	return ETetrominoShape(rand() % ATetromino::SHAPE_COUNT);
}

ABlock* APlayField::CreateBlock(FVector2D FieldPosition)
{
	FVector SpawnLocation = this->GetFieldPositionLocation(FieldPosition);

	return this->GetWorld()->SpawnActor<ABlock>(SpawnLocation, FRotator::ZeroRotator);
}

FVector APlayField::GetFieldPositionLocation(FVector2D FieldPosition)
{
	FVector location = this->GetActorLocation();

	location.X += FieldPosition.X * ABlock::SIZE;
	location.Z += FieldPosition.Y * ABlock::SIZE;

	return location;
}

void APlayField::ShiftDown()
{
	this->Shift({ 0, -1 });
}

void APlayField::ShiftLeft()
{
	this->Shift({ -1, 0 });
}

void APlayField::ShiftRight()
{
	this->Shift({ 1, 0 });
}

void APlayField::Shift(FVector2D Direction)
{
	FVector newLocation = this->ActiveTetromino->GetActorLocation();

	newLocation.X += Direction.X * ABlock::SIZE;
	newLocation.Z += Direction.Y * ABlock::SIZE;
	
	UE_LOG(LogTemp, Warning, TEXT("%s -> %s | %s -> %f"), *this->ActiveTetromino->GetActorLocation().ToString(), *newLocation.ToString(), *Direction.ToString(), Direction.X * ABlock::SIZE);

	this->ActiveTetromino->SetActorLocation(newLocation);
}
