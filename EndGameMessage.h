#ifndef EndGameMessage_H
#define EndGameMessage_H

#pragma once

#include "GameMessage.h"
#include "Vector2D.h"

class Vector2D;

class EndGameMessage :public GameMessage
{
public:
	EndGameMessage();
	virtual ~EndGameMessage();

	void process();

private:
	
};

#endif