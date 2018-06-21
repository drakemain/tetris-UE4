// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayField.h"


// Sets default values
APlayField::APlayField()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APlayField::BeginPlay()
{
	Super::BeginPlay();
	
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

