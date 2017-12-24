// Copyright 2017 Micho Todorovich, all rights reserved.

#include "DesignableUserWidget.h"

void UDesignableUserWidget::SynchronizeProperties() {
	Super::SynchronizeProperties();
	OnSynchronizeProperties();
}
