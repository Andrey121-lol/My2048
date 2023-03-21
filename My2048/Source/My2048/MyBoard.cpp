// Fill out your copyright notice in the Description page of Project Settings.

#include "Math/UnrealMathUtility.h"

#include "MyBoard.h"

// Sets default values
AMyBoard::AMyBoard()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	// Создание корневого компонента для пешки
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	// Создание первого спрайта и приаттачивание его к корневому компоненту
	UPaperSpriteComponent* FirstSprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("FirstSprite"));
	FirstSprite->SetupAttachment(RootComponent);
	UPaperSprite* FirstSpriteAsset = LoadObject<UPaperSprite>(nullptr, TEXT("/Game/2048/Board_Sp"));
	FirstSprite->SetSprite(FirstSpriteAsset);
	FirstSprite->SetRelativeRotation(FRotator(0,90,90));
	FirstSprite->SetRelativeLocation(FVector(45.0f, 45.0f, -2.0f));
	
}

void AMyBoard::CreateGame()
{
	IsGameStopped=false;
	iniArrField();
	CreateTextComponents(0,0,0);
	CreateNewNumber();
	CreateNewNumber();
	SetTextArr();
	LogArr();
}

void AMyBoard::CreateNewNumber()
{
	int x,y;
	FMath::SRandInit(12345);
	x=FMath::RandRange(0,SIZE);
	y=FMath::RandRange(0,SIZE);
	if(Field [x][y]==0)
	{
		if (FMath::RandRange(0,10)!=9)
		{
			Field[x][y]=2;
		}
		else
		{
			Field[x][y]=4;
		}
	}
	else if (Field [x][y]==0)
	{
		CreateNewNumber();
	}
	
}

void AMyBoard::CreateTextComponents(float XOffset, float YOffset, float ZOffset)
{
	// Создание массива компонентов текста
	
	for (int32 Row = 0; Row < 4; ++Row)
	{
		for (int32 Column = 0; Column < 4; ++Column)
		{
			
				// Создание текстовой компоненты и добавление ее к корневому компоненту
				UTextRenderComponent* TextComponent = NewObject<UTextRenderComponent>(RootComponent);
				TextComponent->RegisterComponent();
				ArrText[Row][Column] = TextComponent;

				// Установка размера и текста компоненты
				TextComponent->SetRelativeLocation(FVector(Column * 32.0f, Row * 32.0f, 0.0f));
				TextComponent->SetRelativeRotation(FRotator(90.0f, 0.0f, 0.0f));
				TextComponent->SetHorizontalAlignment(EHTA_Center);
				TextComponent->SetVerticalAlignment(EVRTA_TextCenter);
				TextComponent->SetWorldSize(25.0f);
				TextComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
			
		}
	}
}

void AMyBoard::SetTextArr()
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if(Field[i][j]!=0)
			{
				ArrText[i][j]->SetText(FText::AsNumber(Field[i][j]));
			}
			else
			{
				ArrText[i][j]->SetText(FText::FromString(" "));
			}
		}
	}
	
}

void AMyBoard::LogArr()
{
	UE_LOG(LogTemp, Warning, TEXT("score= %d"), score);
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			UE_LOG(LogTemp, Warning, TEXT("field[%d][%d] = %d"), i, j, Field[i][j]);
		}
	}
}

void AMyBoard::iniArrField()//при инициализации все обнуляется 
{
	score=0;
	Field[SIZE][SIZE]={0};
}

void AMyBoard::MoveDown()
{
	
	for (int i = 0; i < SIZE; i++) {
		int k = SIZE - 1;
		for (int j = SIZE - 2; j >= 0; j--) {
			if (Field[i][j] != 0) {
				if (Field[i][k] == 0) {
					Field[i][k] = Field[i][j];
					Field[i][j] = 0;
				}
				else if (Field[i][k] == Field[i][j]) {
					Field[i][k] *= 2;
					Field[i][j] = 0;
					score+=Field[i][k];//в других методах меняются только  i and k местами 
					k--;
				}
				else {
					k--;
					if (k != j) {
						Field[i][k] = Field[i][j];
						Field[i][j] = 0;
					}
				}
			}
		}
	}
}

void AMyBoard::MoveRight()
{
	for (int j = 0; j < SIZE; j++) {
		int k = 0;
		for (int i = 1; i < SIZE; i++) {
			if (Field[i][j] != 0) {
				if (Field[k][j] == 0) {
					Field[k][j] = Field[i][j];
					Field[i][j] = 0;
				}
				else if (Field[k][j] == Field[i][j]) {
					Field[k][j] *= 2;
					Field[i][j] = 0;
					score+=Field[k][j];
					k++;
				}
				else {
					k++;
					if (k != i) {
						Field[k][j] = Field[i][j];
						Field[i][j] = 0;
					}
				}
			}
		}
	}
}

bool AMyBoard::CanMoveDown() const
{
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			if (Field[i][j] != 0 && i < SIZE - 1 && (Field[i+1][j] == 0 || Field[i+1][j] == Field[i][j])) {
				return true;
			}
		}
	}
	return false;
}


void AMyBoard::MoveUp()
{
	for (int i = 0; i < SIZE; i++) {
		int k = 0;
		for (int j = 1; j < SIZE; j++) {
			if (Field[i][j] != 0) {
				if (Field[i][k] == 0) {
					Field[i][k] = Field[i][j];
					Field[i][j] = 0;
				}
				else if (Field[i][k] == Field[i][j]) {
					Field[i][k] *= 2;
					Field[i][j] = 0;
					score+=Field[i][k];
					k++;
				}
				else {
					k++;
					if (k != j) {
						Field[i][k] = Field[i][j];
						Field[i][j] = 0;
					}
				}
			}
		}
	}
}

void AMyBoard::MoveLeft()
{
	for (int j = 0; j < SIZE; j++) {
		int k = SIZE - 1;
		for (int i = SIZE - 2; i >= 0; i--) {
			if (Field[i][j] != 0) {
				if (Field[k][j] == 0) {
					Field[k][j] = Field[i][j];
					Field[i][j] = 0;
				}
				else if (Field[k][j] == Field[i][j]) {
					Field[k][j] *= 2;
					Field[i][j] = 0;
					score+=Field[k][j];
					k--;
				}
				else {
					k--;
					if (k != i) {
						Field[k][j] = Field[i][j];
						Field[i][j] = 0;
					}
				}
			}
		}
	}
}

// Called when the game starts or when spawned
void AMyBoard::BeginPlay()
{
	Super::BeginPlay();
	CreateGame();
}

// Called every frame
void AMyBoard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}
//input
void AMyBoard::OnLeftInputPressed()
{
	UE_LOG(LogTemp, Warning, TEXT("Left"));
	MoveLeft();
	CreateNewNumber();
	LogArr();
	SetTextArr();
	
}

void AMyBoard::OnRightInputPressed()
{
	UE_LOG(LogTemp, Warning, TEXT("Right"));
	MoveRight();
	CreateNewNumber();
	LogArr();
	SetTextArr();
}

void AMyBoard::OnUpInputPressed()
{
	UE_LOG(LogTemp, Warning, TEXT("Up"));
	MoveUp();
	CreateNewNumber();
	LogArr();
	SetTextArr();

}

void AMyBoard::OnDownInputPressed()
{
	UE_LOG(LogTemp, Warning, TEXT("Down"));
	MoveDown();
	CreateNewNumber();
	LogArr();
	SetTextArr();
}

// Called to bind functionality to input
void AMyBoard::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("LeftInput",IE_Pressed, this, &AMyBoard::OnLeftInputPressed);
	PlayerInputComponent->BindAction("RightInput",IE_Pressed, this, &AMyBoard::OnRightInputPressed);
	PlayerInputComponent->BindAction("UpInput",IE_Pressed, this, &AMyBoard::OnUpInputPressed);
	PlayerInputComponent->BindAction("DownInput",IE_Pressed, this, &AMyBoard::OnDownInputPressed);

}

