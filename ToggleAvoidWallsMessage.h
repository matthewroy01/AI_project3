#ifndef ToggleAvoidWallsMessage_H
#define ToggleAvoidWallsMessage_H

#pragma once

#include "GameMessage.h"
#include "Vector2D.h"

class Vector2D;

class ToggleAvoidWallsMessage :public GameMessage
{
public:
	ToggleAvoidWallsMessage();
	virtual ~ToggleAvoidWallsMessage();

	void process();

private:

};

#endif