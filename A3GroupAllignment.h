#ifndef A3GROUPALLIGNMENT_H
#define A3GROUPALLIGNMENT_H

#include "Steering.h"

class KinematicUnit;

class A3GroupAllignment : public Steering
{
public:
	A3GroupAllignment(KinematicUnit* pMover);
	~A3GroupAllignment() {};

	virtual Steering* getSteering();

private:
	KinematicUnit* mpMover;
};

#endif