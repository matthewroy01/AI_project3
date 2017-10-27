#ifndef TOGGLEDISPLAYINFOMESSAGE_H
#define TOGGLEDISPLAYINFOMESSAGE_H

#pragma once

#include "GameMessage.h"

class ToggleDisplayInfoMessage :public GameMessage
{
public:
	ToggleDisplayInfoMessage();
	~ToggleDisplayInfoMessage();

	void process();

private:
	
};

#endif