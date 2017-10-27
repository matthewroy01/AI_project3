#pragma once

#include "GameMessage.h"
#include "Vector2D.h"

class Vector2D;

class UnitCreateSeekMessage :public GameMessage
{
public:
	UnitCreateSeekMessage();
	~UnitCreateSeekMessage();

	void process();

private:

};