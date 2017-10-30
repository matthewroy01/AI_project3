#include "A3Cohesion.h"

#include "KinematicUnit.h"
#include "Game.h"
#include "UnitManager.h"
#include <math.h>

A3Cohesion::A3Cohesion(KinematicUnit* mover)
{
	mpMover = mover;
}

Steering* A3Cohesion::getSteering()
{
	// code found on page 82-83 of the book

	std::vector <Vector2D> closePos;

	// look at all Units and get the positions of the ones within a certain radius
	for (int i = 1; i < gpGame->getUnitManager()->getNumberOfUnits(); i++)
	{
		if (getDistance(gpGame->getUnitManager()->GetUnit(i)) < 100)
		{
			closePos.push_back(gpGame->getUnitManager()->GetUnit(i)->getPosition());
		}
	}

	if (closePos.size() > 1)
	{
		//std::cout << "cohesion" << std::endl;
	}

	// calculate the average position
	for (unsigned int i = 0; i < closePos.size(); i++)
	{
		mAveragePosition += closePos[i];
	}
	mAveragePosition /= closePos.size();

	// calculate the direction to the average position
	Vector2D direction = mAveragePosition - mpMover->getPosition();
	// calculate the distance between the mover and the average position
	float distance = getDistance(mAveragePosition);
	// calculate the strength of the separation (also don't divide by zero)
	float strength = min((DECAY_COEF_COH * -1) / ((distance * distance) + 1), mpMover->getMaxAcceleration());

	// add the acceleration
	direction.normalize();
	mLinear += direction * strength;

	return this;
}

float A3Cohesion::getDistance(KinematicUnit* target)
{
	// return the distance between the mover and the target
	return sqrt(pow(mpMover->getPosition().getX() - target->getPosition().getX(), 2.0f)
		+ pow(mpMover->getPosition().getY() - target->getPosition().getY(), 2.0f));
}

float A3Cohesion::getDistance(Vector2D target)
{
	// return the distance between the mover and the target
	return sqrt(pow(mpMover->getPosition().getX() - target.getX(), 2.0f)
		+ pow(mpMover->getPosition().getY() - target.getY(), 2.0f));
}