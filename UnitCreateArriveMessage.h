#pragma once

#include "GameMessage.h"
#include "Vector2D.h"

class Vector2D;

class UnitCreateArriveMessage :public GameMessage
{
public:
	UnitCreateArriveMessage();
	~UnitCreateArriveMessage();

	void process();

private:

};