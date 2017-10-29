#ifndef A3VELOCITYMATCH_H
#define A3VELOCITYMATCH_H

#include "Steering.h"
#include <vector>

class KinematicUnit;

class A3VelocityMatch : public Steering
{
public:
	A3VelocityMatch(KinematicUnit* pMover);
	~A3VelocityMatch();

	virtual Steering* getSteering();

	float getDistance(KinematicUnit* target);

private:
	std::vector <KinematicUnit*> mpCloseUnits;

	KinematicUnit* mpMover;
	Vector2D mAverageVelocity;
};

#endif