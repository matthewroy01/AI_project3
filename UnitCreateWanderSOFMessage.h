#pragma once

#include "GameMessage.h"
#include "Vector2D.h"

class Vector2D;

class UnitCreateWanderSOFMessage : public GameMessage
{
public:
	UnitCreateWanderSOFMessage(bool shouldFlee);
	~UnitCreateWanderSOFMessage();

	void process();

private:
	bool mShouldFlee;
};