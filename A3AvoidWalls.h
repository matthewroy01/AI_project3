#ifndef A3AVOIDWALLS_H
#define A3AVOIDWALLS_H

#include "Steering.h"

class KinematicUnit;
class WallUnit;

class A3AvoidWalls : public Steering
{
public:
	A3AvoidWalls(KinematicUnit* pMover);
	~A3AvoidWalls() {};

	virtual Steering* getSteering();

private:
	KinematicUnit* mpMover;

	bool getRaycast(WallUnit* target);
};

#endif