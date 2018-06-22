// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Block.h"
#include "Tetromino.h"
#include "Runtime/Engine/Classes/Camera/CameraComponent.h"
#include "PlayField.generated.h"

UCLASS()
class TETRIS_API APlayField : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayField();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


private:
	void CreateBorder();

	// Spawns a tetromino at the center-top of the field and sets it as the active tetromino. Pass in 0xFF for a random shape.
	void SpawnNewTetromino(ETetrominoShape Shape);

	ETetrominoShape PickRandomShape();

	// Spawns a block at the given field position
	ABlock* CreateBlock(FVector2D FieldPosition);

	// Map the 2D position on the field to 3d world coordinates
	FVector GetFieldPositionLocation(FVector2D FieldPosition);

	/* User input methods */
	void OnShiftDown();
	void OnShiftLeft();
	void OnShiftRight();
	void OnSpawnTetromino();

	// Move active tetromino to new field position relative to current position
	void Shift(FVector2D Direction);

	// Push active tetromino to PlacedTetrominos and set ActiveTetromino to nullptr
	void PlaceActiveTetromino();

	const int HEIGHT = 20;
	const int WIDTH = 10;
	
	TArray<ABlock*> BorderBlocks;
	TArray<ATetromino*> PlacedTetrominoes;
	ATetromino* ActiveTetromino;

	UPROPERTY(EditAnywhere)
	UCameraComponent* Camera;

	FVector CameraPosition;
};
