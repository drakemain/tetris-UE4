// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Runtime/Engine/Classes/Materials/MaterialInstance.h"
#include "Block.generated.h"

UCLASS()
class TETRIS_API ABlock : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABlock();

	static class UMaterialInstance* MaterialRed;
	static class UMaterialInstance* MaterialGreen;
	static class UMaterialInstance* MaterialGrey;
	static class UMaterialInstance* MaterialYellow;
	static class UMaterialInstance* MaterialCyan;
	static class UMaterialInstance* MaterialPink;
	static class UMaterialInstance* MaterialPurple;


	static const int SIZE = 100;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	int getSize() const;

	void setMaterial(UMaterialInstance* Material);

private:
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere)
	UMaterialInstance* Material;
};
