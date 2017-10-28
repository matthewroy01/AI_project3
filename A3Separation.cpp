#include "A3Separation.h"

#include "KinematicUnit.h"
#include "Game.h"
#include "UnitManager.h"
#include <math.h>

A3Separation::A3Separation(KinematicUnit* mover)
{

}

Steering* A3Separation::getSteering()
{
	std::vector <Vector2D> closePos;

	// look at all Units and get the positions of the ones within a certain radius
	for (int i = 0; i < gpGame->getUnitManager()->getNumberOfUnits(); i++)
	{
		if (getDistance(gpGame->getUnitManager()->GetUnit(i)) < 400)
		{
			closePos.push_back(gpGame->getUnitManager()->GetUnit(i)->getPosition());
		}
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
	// calculate the strength of the separation
	float strength = min(DECAY_COEF_SEP / (distance * distance), mpMover->getMaxAcceleration());

	// add the acceleration
	direction.normalize();
	mLinear += direction * strength;

	return this;
}

float A3Separation::getDistance(KinematicUnit* target)
{
	// return the distance between the mover and the target
	return sqrt(pow(mpMover->getPosition().getX() - target->getPosition().getX(), 2.0f)
		+ pow(mpMover->getPosition().getY() - target->getPosition().getY(), 2.0f));
}

float A3Separation::getDistance(Vector2D target)
{
	// return the distance between the mover and the target
	return sqrt(pow(mpMover->getPosition().getX() - target.getX(), 2.0f)
		+ pow(mpMover->getPosition().getY() - target.getY(), 2.0f));
}