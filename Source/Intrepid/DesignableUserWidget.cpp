// Fill out your copyright notice in the Description page of Project Settings.

#include "DesignableUserWidget.h"


//void UDesignableUserWidget::OnSynchronizeProperties_Implementation()
//{
//	// Override this event in Blueprint
//}

void UDesignableUserWidget::SynchronizeProperties() {
	Super::SynchronizeProperties();
	OnSynchronizeProperties();
}