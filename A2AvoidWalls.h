#ifndef A2AVOIDWALLS_H
#define A2AVOIDWALLS_H

#include "Steering.h"

class KinematicUnit;

class A2AvoidWalls : public Steering
{
public:
	A2AvoidWalls(KinematicUnit* pMover);
	~A2AvoidWalls() {};

	virtual Steering* getSteering();

private:
	KinematicUnit* mpMover;

	bool getBoxOnBox(KinematicUnit* target);
	bool getRaycast(KinematicUnit* target);
};

#endif