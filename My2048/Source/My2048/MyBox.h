// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Runtime/Engine/Classes/Components/TextRenderComponent.h"
#include "MyBox.generated.h"

UCLASS()
class MY2048_API AMyBox : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyBox();
	UTextRenderComponent* TextRenderComponent;
	int BoxValue;
	void SetTextFromInt(int32 Value);
	
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
