#pragma once

#include "Trackable.h"

enum MessageType
{
	INVALID_MESSAGE_TYPE = -1,
	PLAYER_MOVETO_MESSAGE = 0,
	UNIT_CREATE_ARRIVE_MESSAGE = 1,
	UNIT_CREATE_SEEK_MESSAGE = 2,
	UNIT_DELETE_RANDOM_MESSAGE = 3,
	UNIT_CREATE_WANDER_SEEK = 4,
	UNIT_CREATE_WANDER_FLEE = 5,
	CHANGE_MODE_MESSAGE = 6,
	CHANGE_MODE_VALUE_MESSAGE = 7,
	TOGGLE_DISPLAY_INFO_MESSAGE = 8,
	END_GAME_MESSAGE = 9
};

class GameMessage: public Trackable
{
public:
	friend class GameMessageManager;

	GameMessage( MessageType type  );
	virtual ~GameMessage();

	double getSubmittedTime() const { return mSubmittedTime; };
	double getScheduledTime() const { return mScheduledTime; };

protected:
	MessageType mType;
	double mSubmittedTime;
	double mScheduledTime;

private:
	virtual void process() = 0; 
};

