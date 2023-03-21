// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MyBox.h"
#include "Engine/Classes/Components/SplineComponent.h"
#include "Components/SceneComponent.h"
//#include "Components/SpriteComponent.h"
#include "Runtime/Engine/Classes/Components/TextRenderComponent.h"
#include "PaperSprite.h"
#include "PaperSpriteComponent.h"
#include "MyBoard.generated.h"


const int SIZE=4;

UCLASS()
class MY2048_API AMyBoard : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMyBoard();
	//ref
	UTextRenderComponent* ArrText[SIZE][SIZE];
	UTextRenderComponent* ScoreText;
	//var-s
	bool IsGameStopped;
	int Field[SIZE][SIZE];
	bool bChangesMade;
	int score;
	bool bMoved;
	//func
	void CreateGame();
	void CreateNewNumber();
	void CreateTextComponents(float XOffset, float YOffset, float ZOffset);
	void SetTextArr();
	void LogArr();
	void iniArrField();
	void MoveDown();
	void MoveUp();
	void MoveLeft();
	void MoveRight();
	bool CanMoveDown() const;
	bool CanMoveUp() const;
	bool CanMoveLeft() const;
	bool CanMoveRight() const;
	
	
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void OnLeftInputPressed();
	void OnRightInputPressed();
	void OnUpInputPressed();
	void OnDownInputPressed();
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
