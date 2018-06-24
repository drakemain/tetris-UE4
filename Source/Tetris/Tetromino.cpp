// Fill out your copyright notice in the Description page of Project Settings.

#include "Tetromino.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Runtime/Engine/Public/DrawDebugHelpers.h"

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
	{ 2, 2 }
};

TTetrominoShape SHAPE_L
{
	{ 0, 3 },
	{ 0, 3 },
	{ 3, 3 }
};

TTetrominoShape SHAPE_O
{
	{ 4, 4 },
	{ 4, 4 }
};

TTetrominoShape SHAPE_S
{
	{ 0, 5, 5 },
	{ 5, 5, 0 }
};

TTetrominoShape SHAPE_T
{
	{ 6, 6, 6 },
	{ 0, 6, 0 }
};

TTetrominoShape SHAPE_Z
{
	{ 7, 7, 0 },
	{ 0, 7, 7 }
};

// Sets default values
ATetromino::ATetromino()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	this->SetRootComponent(CreateDefaultSubobject<USceneComponent>(TEXT("Root")));
	this->Center = CreateDefaultSubobject<USceneComponent>(TEXT("Center"));
}

// Called when the game starts or when spawned
void ATetromino::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ATetromino::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector TopLeft = this->Center->GetComponentLocation();
	FVector TopRight = this->Center->GetComponentLocation();
	FVector BottomLeft = this->Center->GetComponentLocation();
	FVector BottomRight = this->Center->GetComponentLocation();

	TopLeft.X -= (float)this->ShapeDimensions.X / 2.f * ABlock::SIZE; TopLeft.Z += (float)this->ShapeDimensions.Y / 2.f * ABlock::SIZE;
	TopRight.X += (float)this->ShapeDimensions.X / 2.f * ABlock::SIZE; TopRight.Z += (float)this->ShapeDimensions.Y / 2.f * ABlock::SIZE;
	BottomLeft.X -= (float)this->ShapeDimensions.X / 2.f * ABlock::SIZE; BottomLeft.Z -= (float)this->ShapeDimensions.Y / 2.f * ABlock::SIZE;
	BottomRight.X += (float)this->ShapeDimensions.X / 2.f * ABlock::SIZE; BottomRight.Z -= (float)this->ShapeDimensions.Y / 2.f * ABlock::SIZE;

	DrawDebugSphere(
		this->GetWorld(),
		TopLeft,
		10.f,
		20,
		FColor::Black,
		false,
		.1f
	);
	DrawDebugSphere(
		this->GetWorld(),
		TopRight,
		10.f,
		20,
		FColor::Black,
		false,
		.1f
	);
	DrawDebugSphere(
		this->GetWorld(),
		BottomLeft,
		10.f,
		20,
		FColor::Black,
		false,
		.1f
	);
	DrawDebugSphere(
		this->GetWorld(),
		BottomRight,
		10.f,
		20,
		FColor::Black,
		false,
		.1f
	);
	DrawDebugSphere(
		this->GetWorld(),
		this->Center->GetComponentLocation(),
		105.f,
		20,
		FColor::Black,
		false,
		.1f
	);
	DrawDebugSphere(
		this->GetWorld(),
		this->GetActorLocation(),
		51.f,
		20,
		FColor::Blue,
		false,
		.1f
	);
}

void ATetromino::Rotate()
{
	++this->RotationState;

	if (this->RotationState >= 4) 
	{
		this->RotationState = 0;
	}



	FRotator Rotation{ -90.f, 0.f, 0.f };
	
	this->RootComponent->AddLocalRotation(Rotation);

	int temp = this->ShapeDimensions.X;
	this->ShapeDimensions.X = this->ShapeDimensions.Y;
	this->ShapeDimensions.Y = temp;
}

void ATetromino::GenerateShape(ETetrominoShape Shape)
{
	this->Reset();

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
		this->ShapeDimensions.X = ShapeMatrix->operator[](0).Num();
		this->ShapeDimensions.Y = ShapeMatrix->Num();

		for (int i = 0; i < this->ShapeDimensions.Y; ++i)
		{
			for (int j = 0; j < this->ShapeDimensions.X; ++j)
			{
				if (ShapeMatrix->operator[](i)[j] != 0)
				{
					this->Blocks.Push(this->spawnBlock({ (float)j, (float)ShapeMatrix->Num() - i - 1 }));
					this->Blocks.Last()->setMaterial(this->MapMaterial(ShapeMatrix->operator[](i)[j]));
				}
			}
		}

		FVector Center = this->GetActorLocation();

		Center.X += ((float)this->ShapeDimensions.X / 2.f * (float)ABlock::SIZE) - (float)ABlock::SIZE / 2.f;
		Center.Z += (((float)this->ShapeDimensions.Y * (float)ABlock::SIZE) / 2.f);

		this->RootComponent->AddRelativeLocation({ 0.f, 0.f, (float)ABlock::SIZE / 2.f });

		this->Center->SetWorldLocation(Center);
		this->Center->AttachToComponent(this->RootComponent, FAttachmentTransformRules::KeepWorldTransform);

		for (ABlock* Block : this->Blocks)
		{
			Block->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
		}
	}
}

FIntPoint ATetromino::GetDimensions() const
{
	return this->ShapeDimensions;
}

ABlock* ATetromino::spawnBlock(FVector2D OffsetLocation)
{
	FVector BlockLocation = this->GetActorLocation();
	BlockLocation.X += OffsetLocation.X * ABlock::SIZE;
	BlockLocation.Z += OffsetLocation.Y * ABlock::SIZE;

	ABlock* newBlock = this->GetWorld()->SpawnActor<ABlock>(BlockLocation, FRotator::ZeroRotator);

	return newBlock;
}

void ATetromino::Reset()
{
	for (ABlock* block : this->Blocks)
	{
		block->Destroy();
	}

	this->Blocks.Empty(4);

	this->ShapeDimensions = FIntPoint::ZeroValue;

	this->Center->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);

	this->RotationState = 0;
	
	this->RootComponent->AddRelativeLocation({ 0.f, 0.f, -(float)ABlock::SIZE / 2.f });
}

UMaterialInstance * ATetromino::MapMaterial(uint8 MaterialIndex)
{
	switch (MaterialIndex)
	{
	case 0: return nullptr;

	case 1:	return ABlock::MaterialCyan;

	case 2: return ABlock::MaterialPurple;

	case 3: return ABlock::MaterialPink;

	case 4: return ABlock::MaterialGrey;

	case 5: return ABlock::MaterialRed;

	case 6: return ABlock::MaterialYellow;

	case 7: return ABlock::MaterialGreen;

	default: return nullptr;
	}
}
