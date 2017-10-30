#include "A3GroupAllignment.h"

#include "KinematicUnit.h"

A3GroupAllignment::A3GroupAllignment(KinematicUnit* mover)
{
	mpMover = mover;
}

Steering* A3GroupAllignment::getSteering()
{
	// velocity matching handles this already because the boids always face in the direction of their velocity
	return this;
}