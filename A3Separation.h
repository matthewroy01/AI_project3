#ifndef A3SEPARATION_H
#define A3SEPARATION_H

#include "Steering.h"

class KinematicUnit;

class A3Separation : public Steering
{
public:
	A3Separation(KinematicUnit* pMover);
	~A3Separation() {};

	virtual Steering* getSteering();

private:
	KinematicUnit* mpMover;
};

#endif