#ifndef A3VELOCITYMATCH_H
#define A3VELOCITYMATCH_H

#include "Steering.h"

class KinematicUnit;

class A3VelocityMatch : public Steering
{
public:
	A3VelocityMatch(KinematicUnit* pMover);
	~A3VelocityMatch() {};

	virtual Steering* getSteering();

private:
	KinematicUnit* mpMover;
};

#endif