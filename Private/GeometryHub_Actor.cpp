// Fill out your copyright notice in the Description page of Project Settings.


#include "GeometryHub_Actor.h"
#include "Engine/World.h"

// Sets default values
AGeometryHub_Actor::AGeometryHub_Actor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGeometryHub_Actor::BeginPlay()
{
	Super::BeginPlay();
	
	//� UWorld ���������� ������� ������, ��� �� ���� ������� ��� ������ ����� ����� ��������� � ���� - GetWorld 
	UWorld* World = GetWorld();

	//��������, �� ������ �� �������� ������������
	if (World)
	{
		//����� ��������� � ������ ��������� 
		World->SpawnActor(GeometryClass);
	}
}

// Called every frame
void AGeometryHub_Actor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

