// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TestyActor.h"
#include "GeometryHub_Actor.generated.h"


UCLASS()
class LESOINPROJECT_API AGeometryHub_Actor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGeometryHub_Actor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	TSubclassOf<ATestyActor> GeometryClass;

	UPROPERTY(EditAnywhere)
	// Базовый тип класса в UE называеться UClass
	UClass* Class;

	UPROPERTY(EditAnywhere)
	ATestyActor* GeometryObject;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
