// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Block.h"
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

	const int HEIGHT = 20;
	const int WIDTH = 10;

	ABlock* CreateCell(FVector2D FieldPosition);
	TArray<ABlock*> BorderBlocks;

	UPROPERTY(EditAnywhere)
	UCameraComponent* Camera;

	FVector CameraPosition;
};
