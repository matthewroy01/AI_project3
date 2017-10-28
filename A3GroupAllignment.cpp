#include "A3GroupAllignment.h"

#include "KinematicUnit.h"

A3GroupAllignment::A3GroupAllignment(KinematicUnit* mover)
{
	mpMover = mover;
}

Steering* A3GroupAllignment::getSteering()
{
	return this;
}