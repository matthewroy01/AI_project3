#include "A3Separation.h"

#include "KinematicUnit.h"
#include "Game.h"
#include "UnitManager.h"

A3Separation::A3Separation(KinematicUnit* mover)
{

}

Steering* A3Separation::getSteering()
{
	std::vector <Vector2D> closePos;

	for (int i = 0; i < gpGame->getUnitManager()->getNumberOfUnits(); i++)
	{
		if (getDistance(gpGame->getUnitManager()->GetUnit(i)) < 400)
		{
			closePos.push_back(gpGame->getUnitManager()->GetUnit(i)->getPosition());
		}
	}


	return this;
}

float A3Separation::getDistance(KinematicUnit* target)
{
	// return the distance between the mover and the target
	return sqrt(pow(mpMover->getPosition().getX() - target->getPosition().getX(), 2.0f)
		+ pow(mpMover->getPosition().getY() - target->getPosition().getY(), 2.0f));
}