#include "UnitManager.h"

#include "KinematicUnit.h"
#include <cstdlib>
#include "Game.h"
#include "GameMessageManager.h"
#include "EndGameMessage.h"

UnitManager::UnitManager()
{
	mCurrentMode = vel;

	mAllMaxVelocity = GET_GAME->getAllVelocity();
	mAllAngularVelocity = GET_GAME->getAllAngular();
	mAllRadius = GET_GAME->getAllRadius();
}

UnitManager::~UnitManager()
{
	// delete all units in the vector
	for (unsigned int i = 0; i < mpUnits.size(); i++)
	{
		if (mpUnits[i] != NULL)
		{
			delete mpUnits[i];
		}
	}

	for (unsigned int i = 0; i < mpWalls.size(); i++)
	{
		if (mpWalls[i] != NULL)
		{
			delete mpWalls[i];
		}
	}
}

void UnitManager::AddUnit(KinematicUnit* uni, int AItype)
{
	// add the new unit
	mpUnits.push_back(uni);

	switch (AItype)
	{
		case 0:
		{
			// do nothing! this is the player
			break;
		}
		case 1:
		{
			// dynamic arrive

			// when user hits the 'A' key, add a unit exactly 200 pixels away from the player's location
			// this new unit tries to ARRIVE at the player's current location

			mpUnits[mpUnits.size() - 1]->dynamicArrive(GetUnit(0));
			break;
		}
		case 2:
		{
			// dynamic seek

			// when user hits the 'S' key, add a unit exactly 200 pixels away from the player's location
			// this new unit tries to SEEK at the player's current location

			mpUnits[mpUnits.size() - 1]->dynamicSeek(GetUnit(0));
			break;
		}
		case 3:
		{
			// wander and seek

			// wander and then seek the player once it gets inside a certain radius

			mpUnits[mpUnits.size() - 1]->wanderAndSeek(GetUnit(0));
			break;
		}
		case 4:
		{
			// wander and flee

			// wander and then flee the player once it gets inside a certain radius

			mpUnits[mpUnits.size() - 1]->wanderAndFlee(GetUnit(0));
			break;
		}
	}
}

void UnitManager::AddUnit(KinematicUnit* uni)
{
	mpWalls.push_back(uni);
}

void UnitManager::RemoveRandomUnit()
{
	//delete unit

	// when user hits the 'D' key, delete a random unit (not the player)
	// when all units (besides the player) are deleted, exit the game

	srand(time(NULL));
	unsigned int seed;

	if (mpUnits.size() > 1)
	{
		seed = rand() % (mpUnits.size() - 1) + 1;
	}
	else
	{
		KinematicUnit* tmp = mpUnits[0];
		mpUnits.erase(mpUnits.begin());
		delete tmp;

		GameMessage* pMessage = new EndGameMessage();
		MESSAGE_MANAGER->addMessage(pMessage, 0);

		return;
	}

	KinematicUnit* tmp = mpUnits[seed];
	mpUnits.erase(mpUnits.begin() + seed);
	delete tmp;
}

KinematicUnit* UnitManager::GetUnit(int id)
{
	// return the unit at the specfied id
	if (mpUnits[id] != NULL)
	{
		return mpUnits[id];
	}
	else
	{
		return NULL;
	}
}

KinematicUnit* UnitManager::GetWall(int id)
{
	// return the unit at the specfied id
	if (mpWalls[id] != NULL)
	{
		return mpWalls[id];
	}
	else
	{
		return NULL;
	}
}

void UnitManager::UnitDraw(GraphicsBuffer* buffer)
{
	// draw all walls
	for (unsigned int i = 0; i < mpWalls.size(); i++)
	{
		mpWalls[i]->draw(buffer);
	}

	// draw all units
	for (unsigned int i = 0; i < mpUnits.size(); i++)
	{
		mpUnits[i]->draw(buffer);
	}
}

void UnitManager::UnitUpdate(float t)
{
	// update all units
	for (unsigned int i = 0; i < mpUnits.size(); i++)
	{
		mpUnits[i]->update(t, mAllMaxVelocity, mAllRadius, mAllAngularVelocity);

		// update values according to mode

	}
}

void UnitManager::ChangeCurrentMode(int mode)
{
	switch (mode)
	{
		case 0 :
		{
			// velocity
			mCurrentMode = (Mode)mode;
			break;
		}
		case 1 :
		{
			// radius
			mCurrentMode = (Mode)mode;
			break;
		}
		case 2 :
		{
			// angular velocity
			mCurrentMode = (Mode)mode;
			break;
		}
		default :
		{
			std::cout << "ERROR: " << mode << " is not a viable mode." << std::endl;
			break;
		}
	}
}

int UnitManager::GetCurrentMode()
{
	return mCurrentMode;
}

void UnitManager::changeAllVelocity(bool add)
{
	if (add)
	{
		mAllMaxVelocity += ALL_VELOCITY_CONST;
	}
	else
	{
		mAllMaxVelocity -= ALL_VELOCITY_CONST;
	}
}

void UnitManager::changeAllAngular(bool add)
{
	if (add)
	{
		mAllAngularVelocity += ALL_ANGULAR_CONST;
	}
	else
	{
		mAllAngularVelocity -= ALL_ANGULAR_CONST;
	}
}

void UnitManager::changeAllRadius(bool add)
{
	if (add)
	{
		mAllRadius += ALL_RADIUS_CONST;
	}
	else
	{
		mAllRadius -= ALL_RADIUS_CONST;
	}
}