// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayField.h"

#include "Runtime/Engine/Classes/Engine/World.h"
#include "Runtime/Engine/Public/DrawDebugHelpers.h"


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
		PlayerInputComponent->BindAction("ShiftDown", IE_Pressed, this, &APlayField::OnShiftDown);
		PlayerInputComponent->BindAction("ShiftLeft", IE_Pressed, this, &APlayField::OnShiftLeft);
		PlayerInputComponent->BindAction("ShiftRight", IE_Pressed, this, &APlayField::OnShiftRight);
		PlayerInputComponent->BindAction("Rotate", IE_Pressed, this, &APlayField::OnRotate);

		// Temporary for testing
		PlayerInputComponent->BindAction("SpawnNewTetromino", IE_Pressed, this, &APlayField::OnSpawnTetromino);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No input component!"));
	}

	for (int i = 0; i < this->HEIGHT; ++i)
	{
		for (int j = 0; j < this->WIDTH; ++j)
		{
			FVector Extent;
			DrawDebugPoint(
				this->GetWorld(),
				this->GetFieldPositionLocation({ (float)j, (float)i }),
				10.f,
				FColor::Green,
				true
			);
		}
	}

	DrawDebugCircle(
		this->GetWorld(),
		this->GetFieldPositionLocation({ 0.f, 0.f }),
		51.f,
		20,
		FColor::Green,
		true
	);
}

void APlayField::CreateBorder()
{
	for (int i = -1; i < this->HEIGHT; ++i) 
	{
		this->BorderBlocks.Push(this->CreateBlock({ -1.f, (float)i }));
		this->BorderBlocks.Last()->SetActorLocation(this->BorderBlocks.Last()->GetActorLocation() - FVector{ 0.f, 0.f, (float)ABlock::SIZE / 2.f });
		this->BorderBlocks.Push(this->CreateBlock({ (float)this->WIDTH, (float)i }));
		this->BorderBlocks.Last()->SetActorLocation(this->BorderBlocks.Last()->GetActorLocation() - FVector{ 0.f, 0.f, (float)ABlock::SIZE / 2.f });
	}

	for (int i = 0; i < this->WIDTH; ++i) 
	{
		this->BorderBlocks.Push(this->CreateBlock({ (float)i, -1.f }));
		this->BorderBlocks.Last()->SetActorLocation(this->BorderBlocks.Last()->GetActorLocation() - FVector{ 0.f, 0.f, (float)ABlock::SIZE / 2.f });
	}
}

void APlayField::SpawnNewTetromino(ETetrominoShape Shape)
{
	// Spawn the tetromino centered at the top of the field
	FVector SpawnLocation = this->GetFieldPositionLocation({ FMath::DivideAndRoundDown((float)this->WIDTH, 2.f), (float)this->HEIGHT });

	this->PlaceActiveTetromino();

	this->ActiveTetromino = this->GetWorld()->SpawnActor<ATetromino>(SpawnLocation, FRotator::ZeroRotator);
	
	// Use the max value for uint8 to indicated generation of random shape
	if ((uint8)Shape == 0xFF)
	{
		Shape = this->PickRandomShape();
	}

	this->ActiveTetromino->GenerateShape(Shape);

	// Recenter the tetromino based on its newly generated shape
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

FVector2D APlayField::GetLocationAsFieldPosition(FVector Location)
{
	FVector2D position;

	position.X = FMath::DivideAndRoundDown(Location.X, (float)ABlock::SIZE);
	position.Y = FMath::DivideAndRoundDown(Location.Z, (float)ABlock::SIZE);

	return position;
}

void APlayField::OnShiftDown()
{
	this->Shift({ 0, -1 });
}

void APlayField::OnShiftLeft()
{
	this->Shift({ -1, 0 });
}

void APlayField::OnShiftRight()
{
	this->Shift({ 1, 0 });
}

void APlayField::OnRotate()
{
	this->ActiveTetromino->Rotate();
}

void APlayField::OnSpawnTetromino()
{
	UE_LOG(LogTemp, Warning, TEXT("Spawning a new tetromino."));
	this->SpawnNewTetromino((ETetrominoShape)0xFF);
}

void APlayField::Shift(FVector2D Direction)
{
	if (!this->isMoveInBounds(Direction)) { UE_LOG(LogTemp, Warning, TEXT("OOB"));  return; }

	if (ActiveTetromino)
	{
		FVector newLocation = this->ActiveTetromino->GetActorLocation();

		newLocation.X += Direction.X * ABlock::SIZE;
		newLocation.Z += Direction.Y * ABlock::SIZE;

		UE_LOG(LogTemp, Warning, TEXT("%s -> %s | %s -> %f"), *this->ActiveTetromino->GetActorLocation().ToString(), *newLocation.ToString(), *Direction.ToString(), Direction.X * ABlock::SIZE);

		this->ActiveTetromino->SetActorLocation(newLocation);
	}
}

bool APlayField::isMoveInBounds(FVector2D PositionDelta)
{
	TArray<ABlock*> Blocks;

	this->ActiveTetromino->GetBlocks(Blocks);

	for (ABlock* Block : Blocks)
	{
		FVector2D ProjectedPosition = this->GetLocationAsFieldPosition(Block->getCenterLocation());
		ProjectedPosition.X += PositionDelta.X;
		ProjectedPosition.Y += PositionDelta.Y;

		bool badLeftBound = ProjectedPosition.X < 0;
		bool badRightBound = ProjectedPosition.X > (this->WIDTH) - 1;
		bool badBottomBound = ProjectedPosition.Y < 0;
		
		if (badLeftBound || badRightBound || badBottomBound)
		{
			return false;
		}
	}

	return true;
}

void APlayField::PlaceActiveTetromino()
{
	if (ActiveTetromino)
	{
		this->PlacedTetrominoes.Push(this->ActiveTetromino);
		this->ActiveTetromino = nullptr;
	}
}
