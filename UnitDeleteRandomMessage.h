#pragma once

#include "GameMessage.h"
#include "Vector2D.h"

class Vector2D;

class UnitDeleteRandomMessage :public GameMessage
{
public:
	UnitDeleteRandomMessage();
	~UnitDeleteRandomMessage();

	void process();

private:

};