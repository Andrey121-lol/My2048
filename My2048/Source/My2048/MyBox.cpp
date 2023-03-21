// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBox.h"

// Sets default values
AMyBox::AMyBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//UTextRenderComponent* TextRenderComponent = CreateDefaultSubobject<UTextRenderComponent>(TEXT("TextRenderComponent")); TextRenderComponent = CreateDefaultSubobject<UTextRenderComponent>(TEXT("TextRenderComponent"));
	TextRenderComponent = CreateDefaultSubobject<UTextRenderComponent>(TEXT("TextRenderComponent"));
	TextRenderComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	
	TextRenderComponent->SetHorizontalAlignment(EHorizTextAligment::EHTA_Center);
	TextRenderComponent->SetVerticalAlignment(EVerticalTextAligment::EVRTA_TextCenter);
	TextRenderComponent->SetTextRenderColor(FColor::White);
	//TextRenderComponent->SetTextWorldSize(20.f); // установить размер текста в 20 единиц в мировых координатах
	
}


void AMyBox::SetTextFromInt(int32 Value)
{
	FText MyText = FText::AsNumber(Value); // Преобразуем число в FText
	if (TextRenderComponent != nullptr)
	{
		TextRenderComponent->SetText(MyText); // Устанавливаем текст в компонент
	}
}



// Called when the game starts or when spawned
void AMyBox::BeginPlay()
{
	Super::BeginPlay();
	BoxValue=100000;
	FText xxx = FText::FromString("564654848");
	TextRenderComponent->SetText(xxx);
}

// Called every frame
void AMyBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

