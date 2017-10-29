#include "A3Blend.h"

#include "UnitManager.h"
#include "Game.h"

#include "KinematicUnit.h"

#include "A3Cohesion.h"
#include "A3GroupAllignment.h"
#include "A3Separation.h"
#include "A3VelocityMatch.h"
#include "A2Wander.h"
#include "A3AvoidWalls.h"

A3Blend::A3Blend(KinematicUnit *pMover)
	:mpMover(pMover)
{
	mApplyDirectly = true;

	mpCohesion = new A3Cohesion(mpMover);
	mpGroupAllignment = new A3GroupAllignment(mpMover);
	mpSeparation = new A3Separation(mpMover);
	mpVelocityMatch = new A3VelocityMatch(mpMover);
	mpWander = new A2Wander(mpMover);
	mpAvoidWalls = new A3AvoidWalls(mpMover);
}

A3Blend::~A3Blend()
{
	delete mpCohesion;
	delete mpGroupAllignment;
	delete mpSeparation;
	delete mpVelocityMatch;
	delete mpWander;
	delete mpAvoidWalls;
}

Steering* A3Blend::getSteering()
{
	mpCohesion->getSteering();
	mpGroupAllignment->getSteering();
	mpSeparation->getSteering();
	mpVelocityMatch->getSteering();
	mpWander->getSteering();
	mpAvoidWalls->getSteering();

	setAngular((mpCohesion->getAngular() * W_COHESION) +
		(mpGroupAllignment->getAngular() * W_GROUP_ALLIGNMENT) +
		(mpSeparation->getAngular() * W_SEPARATION) +
		(mpVelocityMatch->getAngular() * W_VELOCITY_MATCH) +
		(mpWander->getAngular() * W_WANDER) +
		(mpAvoidWalls->getAngular() * W_AVOID_WALLS));

	setLinear((mpCohesion->getLinear() * W_COHESION) +
		(mpGroupAllignment->getLinear() * W_GROUP_ALLIGNMENT) +
		(mpSeparation->getLinear() * W_SEPARATION) +
		(mpVelocityMatch->getLinear() * W_VELOCITY_MATCH) +
		(mpWander->getLinear() * W_WANDER) +
		(mpAvoidWalls->getLinear() * W_AVOID_WALLS));

	return this;
}