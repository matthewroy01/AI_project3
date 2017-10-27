#pragma once

#include "GameMessage.h"
#include "Vector2D.h"

class Vector2D;

class ChangeModeMessage :public GameMessage
{
public:
	ChangeModeMessage(int mode);
	~ChangeModeMessage();

	void process();

private:
	int mMode;
};