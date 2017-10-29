#include "A3VelocityMatch.h"

#include "KinematicUnit.h"
#include <vector>
#include "Game.h"
#include "UnitManager.h"

A3VelocityMatch::A3VelocityMatch(KinematicUnit* mover)
{
	mpMover = mover;
}

Steering* A3VelocityMatch::getSteering()
{
	// code found on page 66-67 of the book
	//std::cout << "velocity match" << std::endl;

	float timeToTarget = 0.1f;

	std::vector <KinematicUnit*> closeUnits;

	// for all units, find the ones that are close enough to the mover and add them to the vector
	for (int i = 1; i < gpGame->getUnitManager()->getNumberOfUnits(); i++)
	{
		if (getDistance(gpGame->getUnitManager()->GetUnit(i)) < 100)
		{
			closeUnits.push_back(gpGame->getUnitManager()->GetUnit(i));
		}
	}

	if (closeUnits.size() > 1)
	{
		std::cout << "velocity match" << std::endl;
	}

	// add all velocities together
	for (unsigned int i = 0; i < closeUnits.size(); i++)
	{
		mAverageVelocity += closeUnits[i]->getVelocity();
	}
	// divide by the total to get the average
	mAverageVelocity /= closeUnits.size();

	// set the new linear
	mLinear = mAverageVelocity - mpMover->getVelocity();
	mLinear /= timeToTarget;

	// check to see if we're going too fast and adjust
	if (mLinear.getLength() > mpMover->getMaxAcceleration())
	{
		mLinear.normalize();
		mLinear *= mpMover->getMaxAcceleration();
	}

	return this;
}

float A3VelocityMatch::getDistance(KinematicUnit* target)
{
	// return the distance between the mover and the target
	return sqrt(pow(mpMover->getPosition().getX() - target->getPosition().getX(), 2.0f)
		+ pow(mpMover->getPosition().getY() - target->getPosition().getY(), 2.0f));
}