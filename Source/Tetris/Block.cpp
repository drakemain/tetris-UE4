// Fill out your copyright notice in the Description page of Project Settings.

#include "Block.h"

#include "Runtime/Engine/Classes/Components/StaticMeshComponent.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"
#include "Engine/StaticMesh.h"

UMaterialInstance* ABlock::MaterialRed = nullptr;
UMaterialInstance* ABlock::MaterialGreen = nullptr;
UMaterialInstance* ABlock::MaterialGrey = nullptr;
UMaterialInstance* ABlock::MaterialYellow = nullptr;
UMaterialInstance* ABlock::MaterialCyan = nullptr;
UMaterialInstance* ABlock::MaterialPink = nullptr;
UMaterialInstance* ABlock::MaterialPurple = nullptr;

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

	// Load materials
	if (ABlock::MaterialRed == nullptr)
	{
		static ConstructorHelpers::FObjectFinder<UMaterialInstance> newBlueMaterial(TEXT("MaterialInstanceConstant'/Game/Material/Red.Red'"));

		if (newBlueMaterial.Succeeded())
		{
			ABlock::MaterialRed = newBlueMaterial.Object;
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Failed to load material"));
		}
	}
	if (ABlock::MaterialGreen == nullptr)
	{
		static ConstructorHelpers::FObjectFinder<UMaterialInstance> newBlueMaterial(TEXT("MaterialInstanceConstant'/Game/Material/Green.Green'"));

		if (newBlueMaterial.Succeeded())
		{
			ABlock::MaterialGreen = newBlueMaterial.Object;
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Failed to load material"));
		}
	}
	if (ABlock::MaterialGrey == nullptr)
	{
		static ConstructorHelpers::FObjectFinder<UMaterialInstance> newBlueMaterial(TEXT("MaterialInstanceConstant'/Game/Material/Grey.Grey'"));

		if (newBlueMaterial.Succeeded())
		{
			ABlock::MaterialGrey = newBlueMaterial.Object;
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Failed to load material"));
		}
	}
	if (ABlock::MaterialYellow == nullptr)
	{
		static ConstructorHelpers::FObjectFinder<UMaterialInstance> newBlueMaterial(TEXT("MaterialInstanceConstant'/Game/Material/Yellow.Yellow'"));

		if (newBlueMaterial.Succeeded())
		{
			ABlock::MaterialYellow = newBlueMaterial.Object;
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Failed to load material"));
		}
	}
	if (ABlock::MaterialCyan == nullptr)
	{
		static ConstructorHelpers::FObjectFinder<UMaterialInstance> newBlueMaterial(TEXT("MaterialInstanceConstant'/Game/Material/Cyan.Cyan'"));

		if (newBlueMaterial.Succeeded())
		{
			ABlock::MaterialCyan = newBlueMaterial.Object;
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Failed to load material"));
		}
	}
	if (ABlock::MaterialPink == nullptr)
	{
		static ConstructorHelpers::FObjectFinder<UMaterialInstance> newBlueMaterial(TEXT("MaterialInstanceConstant'/Game/Material/Pink.Pink'"));

		if (newBlueMaterial.Succeeded())
		{
			ABlock::MaterialPink = newBlueMaterial.Object;
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Failed to load material"));
		}
	}
	if (ABlock::MaterialPurple == nullptr)
	{
		static ConstructorHelpers::FObjectFinder<UMaterialInstance> newBlueMaterial(TEXT("MaterialInstanceConstant'/Game/Material/Purple.Purple'"));

		if (newBlueMaterial.Succeeded())
		{
			ABlock::MaterialPurple = newBlueMaterial.Object;
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Failed to load material"));
		}
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

int ABlock::getSize() const
{
	return this->SIZE;
}

void ABlock::setMaterial(UMaterialInstance * Material)
{
	if (Material)
	{
		UE_LOG(LogTemp, Warning, TEXT("Setting material!"));

		this->Material = Material;

		this->Mesh->SetMaterial(0, this->Material);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Bad material reference passed."));
	}
}

