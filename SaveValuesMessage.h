#ifndef SaveValuesMessage_H
#define SaveValuesMessage_H

#pragma once

#include "GameMessage.h"
#include "Vector2D.h"

class Vector2D;

class SaveValuesMessage :public GameMessage
{
public:
	SaveValuesMessage();
	virtual ~SaveValuesMessage();

	void process();

private:

};

#endif