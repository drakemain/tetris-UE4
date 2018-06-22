// Fill out your copyright notice in the Description page of Project Settings.

#include "Tetromino.h"
#include "Runtime/Engine/Classes/Engine/World.h"


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
	
	this->Blocks.Push(this->GetWorld()->SpawnActor<ABlock>(this->GetActorLocation(), FRotator::ZeroRotator));
	this->Blocks.Last()->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
}

// Called every frame
void ATetromino::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

