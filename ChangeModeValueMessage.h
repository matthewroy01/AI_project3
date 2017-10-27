#pragma once

#include "GameMessage.h"
#include "Vector2D.h"

class Vector2D;

class ChangeModeValueMessage : public GameMessage
{
public:
	ChangeModeValueMessage(int modeNum, bool add);
	~ChangeModeValueMessage();

	void process();

private:
	bool mAdd;
	int mModeNum;
};