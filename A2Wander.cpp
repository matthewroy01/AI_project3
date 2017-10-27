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
	// overwrite the wander rotation for modes
	//float angularVelocity = mpMover->getAngularVelocity();
	float angularVelocityRate = 0.5f;

	//mpMover->setNewOrientation();
	// wander
	// multiply the behavior by the constant because it doesn't work without it...
	mLinear = (mpMover->getOrientationAsVector() * mpMover->getMaxVelocity()) * (1 / W_WANDER);
	mAngular = (mpMover->getOrientation() + (genRandomBinomial() * angularVelocityRate)) * (1 / W_WANDER);

	return this;
}