// Fill out your copyright notice in the Description page of Project Settings.

#include "Tetromino.h"
#include "Runtime/Engine/Classes/Engine/World.h"

typedef const TArray<TArray<uint8>> TTetrominoShape;

TTetrominoShape SHAPE_I 
{
	{ 1 },
	{ 1 },
	{ 1 },
	{ 1 }
};

TTetrominoShape SHAPE_J
{
	{ 2, 0 },
	{ 2, 0 },
	{ 2, 0 },
	{ 2, 2 }
};

TTetrominoShape SHAPE_L
{
	{ 0, 3 },
	{ 0, 3 },
	{ 0, 3 },
	{ 3, 3 }
};

TTetrominoShape SHAPE_O
{
	{ 1, 1 },
	{ 1, 1 }
};

TTetrominoShape SHAPE_S
{
	{ 0, 1, 1 },
	{ 1, 1, 0 }
};

TTetrominoShape SHAPE_T
{
	{ 1, 1, 1 },
	{ 0, 1, 0 }
};

TTetrominoShape SHAPE_Z
{
	{ 1, 1, 0 },
	{ 0, 1, 1 }
};

// Sets default values
ATetromino::ATetromino()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	this->RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
}

// Called when the game starts or when spawned
void ATetromino::BeginPlay()
{
	Super::BeginPlay();
	this->GenerateShape(ETetrominoShape::S);
}

// Called every frame
void ATetromino::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATetromino::GenerateShape(ETetrominoShape Shape)
{
	for (ABlock* block : this->Blocks)
	{
		block->Destroy();
	}

	this->Blocks.Empty(4);

	const TTetrominoShape* ShapeMatrix;

	switch (Shape)
	{
	case ETetrominoShape::I:
		ShapeMatrix = &SHAPE_I; break;

	case ETetrominoShape::J:
		ShapeMatrix = &SHAPE_J; break;

	case ETetrominoShape::L:
		ShapeMatrix = &SHAPE_L; break;

	case ETetrominoShape::O:
		ShapeMatrix = &SHAPE_O; break;

	case ETetrominoShape::S:
		ShapeMatrix = &SHAPE_S; break;

	case ETetrominoShape::T:
		ShapeMatrix = &SHAPE_T; break;

	case ETetrominoShape::Z:
		ShapeMatrix = &SHAPE_Z; break;

	default:
		ShapeMatrix = nullptr; break;
	}

	if (ShapeMatrix != nullptr)
	{
		for (int i = 0; i < ShapeMatrix->Num(); ++i)
		{
			for (int j = 0; j < ShapeMatrix->operator[](i).Num(); ++j)
			{
				if (ShapeMatrix->operator[](i)[j] != 0)
				{
					this->spawnBlock({ (float)j, (float)ShapeMatrix->Num() - i });
				}
			}
		}
	}
}

void ATetromino::spawnBlock(FVector2D OffsetLocation)
{
	FVector BlockLocation = this->GetActorLocation();
	BlockLocation.X += OffsetLocation.X * ABlock::SIZE;
	BlockLocation.Z += OffsetLocation.Y * ABlock::SIZE;

	this->Blocks.Push(this->GetWorld()->SpawnActor<ABlock>(BlockLocation, FRotator::ZeroRotator));
	this->Blocks.Last()->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
}