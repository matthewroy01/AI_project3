#ifndef UNITCREATEFIVEBOIDSMESSAGE_H
#define UNITCREATEFIVEBOIDSMESSAGE_H

#include "GameMessage.h"
#include "Vector2D.h"

class Vector2D;

class UnitCreateFiveBoidsMessage :public GameMessage
{
public:
	UnitCreateFiveBoidsMessage();
	~UnitCreateFiveBoidsMessage();

	void process();

private:

};

#endif