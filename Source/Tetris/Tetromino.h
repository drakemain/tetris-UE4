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

	static const uint8 SHAPE_COUNT = 7;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void GenerateShape(ETetrominoShape Shape);

	FIntPoint GetDimensions() const;

private:
	void spawnBlock(FVector2D OffsetLocation);

	TArray<ABlock*> Blocks;

	FIntPoint ShapeDimensions = FIntPoint::ZeroValue;
};
