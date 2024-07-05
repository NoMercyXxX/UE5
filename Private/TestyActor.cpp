// Fill out your copyright notice in the Description page of Project Settings.


#include "TestyActor.h"
#include "Engine/Engine.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "TimerManager.h"

DEFINE_LOG_CATEGORY_STATIC(LogTesty, All, All)

// Sets default values
ATestyActor::ATestyActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>("BaseMesh");
	SetRootComponent(BaseMesh);
}

// Called when the game starts or when spawned
void ATestyActor::BeginPlay()
{
	Super::BeginPlay();

	initialLocation = GetActorLocation();

	
	/*PrintTransform();*/
	/*PrintStringTypes();*/
	/*PrintTypes();*/
	SetColor(GeometryData.Color);
	GetWorldTimerManager().SetTimer(TimerHandle, this, &ATestyActor::OnTimerFired, GeometryData.TimerRate, true);

}

// Called every frame
void ATestyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	HandleMovement();
}

void ATestyActor::HandleMovement()
{
	switch (GeometryData.MoveType)
	{
	case EMovementType::Sin:
	{
		FVector CurrentLocation = GetActorLocation();
		float Time = GetWorld()->GetTimeSeconds();
		CurrentLocation.Y = initialLocation.Y + GeometryData.Amplitude * FMath::Sin(GeometryData.Frequency * Time);
		SetActorLocation(CurrentLocation);
	}
	break;
	case EMovementType::Static:
		break;
	default:
		break;
	}
}

void ATestyActor::PrintTypes()
{
	UE_LOG(LogTesty, Warning, TEXT("Actor name: %s"), *GetName());
	UE_LOG(LogTesty, Warning, TEXT("Weapons num: %d"), WeaponsNum);
	UE_LOG(LogTesty, Warning, TEXT("Kills num: %i"), KillsNum);
	UE_LOG(LogTesty, Warning, TEXT("Health: %f"), Health);
	UE_LOG(LogTesty, Warning, TEXT("IsDead: %d"), IsDead);
	UE_LOG(LogTesty, Warning, TEXT("HasWeapon: %d"), static_cast<int>(HasWeapon));
}

void ATestyActor::PrintStringTypes()
{

	FString Name = "Nick Valentine";
	UE_LOG(LogTesty, Display, TEXT("Name: %s"), *Name);

	FString WeaponsNumStr = "Weapons num = " + FString::FromInt(WeaponsNum);
	FString HealthStr = "Health = " + FString::SanitizeFloat(Health);
	FString IsDeadStr = "Is Dead = " + FString(IsDead ? "true" : "false");

	FString Stat = FString::Printf(TEXT(" \n == All Stat == \n %s \n %s \n %s"), *WeaponsNumStr, *HealthStr, *IsDeadStr);
	UE_LOG(LogTesty, Warning, TEXT("%s"), *Stat);

	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, Name);
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, Stat, true, FVector2D(1.5f, 1.5f));

}

void ATestyActor::PrintTransform()
{
	FTransform Transform = GetActorTransform();
	FVector Location = Transform.GetLocation();
	FRotator Rotation = Transform.Rotator();
	FVector Scale = Transform.GetScale3D();

	UE_LOG(LogTesty, Warning, TEXT("Actor name: %s"), *GetName());
	UE_LOG(LogTesty, Warning, TEXT("Transform %s"), *Transform.ToString());
	UE_LOG(LogTesty, Warning, TEXT("Location %s"), *Location.ToString());
	UE_LOG(LogTesty, Warning, TEXT("Rotation %s"), *Rotation.ToString());
	UE_LOG(LogTesty, Warning, TEXT("Scale %s"), *Scale.ToString());

	UE_LOG(LogTesty, Error, TEXT("HumanTransform %s"), *Transform.ToHumanReadableString());
}

void ATestyActor::SetColor(const FLinearColor& Color)
{
	UMaterialInstanceDynamic* DynMaterial = BaseMesh->CreateAndSetMaterialInstanceDynamic(0);
	if (DynMaterial)
	{
		DynMaterial->SetVectorParameterValue("Color", Color);
	}
}

void ATestyActor::OnTimerFired()
{
	// Проверяем если TimerCount меньше максимального колчества срабатываний, то меняем цвет (MaxTimerCount - переменная ограничения срабатывания)
	if (++TimerCount <= MaxTimerCount)
	{
		// Используем FLinearColor для цвета и вызываем статическую функцию для рандомного изменения цвета
		const FLinearColor NewColor = FLinearColor::MakeRandomColor();

		// Вывод изменения цвета в концоль строкой
		UE_LOG(LogTesty, Warning, TEXT("TimerCounts: %i, Color to set up: %s"), TimerCount, *NewColor.ToString());

		// Используем существующую функцию "SetColor" и создадим переменную "NewColor"
		SetColor(NewColor);
	}
	else
	{
		// Вывод сообщения отработки таймера
		UE_LOG(LogTesty, Error, TEXT("Timer has been stopped"));
		GetWorldTimerManager().ClearTimer(TimerHandle);
	}
}


