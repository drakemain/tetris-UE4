// Fill out your copyright notice in the Description page of Project Settings.

#include "Block.h"

#include "Runtime/Engine/Classes/Components/StaticMeshComponent.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"

// Sets default values
ABlock::ABlock()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	this->Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	this->SetRootComponent(this->Mesh);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> newMesh(TEXT("StaticMesh'/Game/Mesh/Cube.Cube'"));

	if (newMesh.Succeeded())
	{
		this->Mesh->SetStaticMesh(newMesh.Object);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to load mesh for %s!"), *this->GetName());
	}
}

// Called when the game starts or when spawned
void ABlock::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ABlock::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

