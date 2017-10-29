#include "A2Wander.h"
#include "KinematicUnit.h"
#include "Game.h"

A2Wander::A2Wander(KinematicUnit *pMover)
	:mpMover(pMover)
{
	mApplyDirectly = true;
}

Steering* A2Wander::getSteering()
{
	float angularVelocityRate = 0.5f;

	// wander
	// multiply the behavior by the weight to help amplify its effects
	mLinear = (mpMover->getOrientationAsVector() * mpMover->getMaxVelocity()) * (1 / W_WANDER);
	mAngular = (mpMover->getOrientation() + (genRandomBinomial() * angularVelocityRate)) * (1 / W_WANDER);

	return this;
}