#include "A3Blend.h"

#include "UnitManager.h"
#include "Game.h"

#include "A2Wander.h"
#include "A3Cohesion.h"
#include "A3GroupAllignment.h"
#include "A3Separation.h"
#include "A3VelocityMatch.h"

A3Blend::A3Blend(KinematicUnit *pMover, KinematicUnit *pTarget, bool shouldFlee)
	:mpMover(pMover),
	mpTarget(pTarget),
	mShouldFlee(shouldFlee)
{
	mApplyDirectly = true;

	Init();
}

void A3Blend::Init()
{
	mpCohesion = new A3Cohesion(mpMover);
	mpGroupAllignment = new A3GroupAllignment(mpMover);
	mpSeparation = new A3Separation(mpMover);
	mpVelocityMatch = new A3VelocityMatch(mpMover);
	mpWander = new A2Wander(mpMover);
}

Steering* A3Blend::getSteering()
{
	return this;
}

void A3Blend::CleanUp()
{
	delete mpCohesion;
	delete mpGroupAllignment;
	delete mpSeparation;
	delete mpVelocityMatch;
	delete mpWander;
}