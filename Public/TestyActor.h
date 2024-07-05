// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "TestyActor.generated.h"

UENUM(BlueprintType)
enum class EMovementType : uint8
{
	Sin,
	Static
};

USTRUCT(BlueprintType)
struct FGeometryData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, Category = "Design")
	FLinearColor Color = FLinearColor::Black;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float Amplitude = 50.0f;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float Frequency = 2.0f;

	UPROPERTY(EditAnywhere, Category = "Movement")
	EMovementType MoveType = EMovementType::Static;

	//Cоздаем переменную таймера и указываем раз в соклько секунд она срабатывает
	UPROPERTY(EditAnywhere, Category = "Timer")
	float TimerRate = 1.0f;
};

UCLASS()
class LESOINPROJECT_API ATestyActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATestyActor();

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* BaseMesh;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "GeometryData")
	FGeometryData GeometryData;

	UPROPERTY(EditAnywhere, Category = "Weapon")
	int32 WeaponsNum = 4;

	UPROPERTY(EditDefaultsOnly, Category = "Stat")
	int32 KillsNum = 7;

	UPROPERTY(EditInstanceOnly, Category = "Health")
	float Health = 35.123f;

	UPROPERTY(EditAnywhere, Category = "Life")
	bool IsDead = false;

	UPROPERTY(EditAnywhere, Category = "Weapon")
	bool HasWeapon = true;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	// Создание переменной таймера и ее название
	FTimerHandle TimerHandle;

	// Переменная для определения сколько раз сработает таймер
	const int32 MaxTimerCount = 5; 

	// Счетчик срабатываня таймера
	int32 TimerCount = 0;

	FVector initialLocation;
	void HandleMovement();
	void PrintTypes();
	void PrintStringTypes();
	void PrintTransform();
	void SetColor(const FLinearColor& Color);

	// Ссылка на тело функции таймера
	void OnTimerFired();
};
