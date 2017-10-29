#include "A3Wander.h"
#include "KinematicUnit.h"
#include "Game.h"
#include "GraphicsSystem.h"

#include <stdlib.h>
#include <time.h>

#include <math.h>

A3Wander::A3Wander(KinematicUnit *pMover)
	:mpMover(pMover)
{
	mApplyDirectly = false;
}

Steering* A3Wander::getSteering()
{
	Vector2D circleCenter;
	circleCenter = mpMover->getVelocity();
	circleCenter.normalize();
	circleCenter = circleCenter * 3;

	Vector2D displacement;
	displacement = (0, genRandomBinomial());
	displacement = displacement * 10;

	displacement.setX(cos(mWanderAngle) * displacement.getLength());
	displacement.setY(sin(mWanderAngle) * displacement.getLength());

	mWanderAngle += (rand() * ANGLE_CHANGE) - (ANGLE_CHANGE * 0.5f);

	mLinear = circleCenter + displacement;
	mLinear.normalize();
	mLinear *= mpMover->getMaxVelocity();
	mLinear.normalize();
	mLinear *= mpMover->getMaxAcceleration();

	mLinear *= 15;

	mAngular = 0;

	return this;
}

float A3Wander::getDistance(Vector2D target)
{
	// return the distance between the mover and the target
	return sqrt(pow(mpMover->getPosition().getX() - target.getX(), 2.0f)
		+ pow(mpMover->getPosition().getY() - target.getY(), 2.0f));
}