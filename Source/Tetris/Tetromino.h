// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Block.h"
#include "Tetromino.generated.h"

enum class ETetrominoShape : uint8
{
	I,
	J,
	L,
	O,
	S,
	T,
	Z
};

UCLASS()
class TETRIS_API ATetromino : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATetromino();

	// Total number of defined shapes
	static const uint8 SHAPE_COUNT = 7;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Spawns blocks in appropriate positions to for the given shape. If there is already a shape, existing blocks will be destroyed first.
	void GenerateShape(ETetrominoShape Shape);

	FIntPoint GetDimensions() const;

private:
	// Spawns a block offset from the instance root by block size
	ABlock* SpawnBlock(FVector2D OffsetLocation);

	// The blocks that the tetromino instance is comprised of
	TArray<ABlock*> Blocks;

	// Dimensions of the generated shape. Value is set when GenerateShape is called.
	FIntPoint ShapeDimensions = FIntPoint::ZeroValue;
};
