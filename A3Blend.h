#ifndef A3BLEND_H
#define A3BLEND_H

#include "Steering.h"

class A3Cohesion;
class A3GroupAllignment;
class A3Separation;
class A3VelocityMatch;
class A2Wander;

class KinematicUnit;

class A3Blend : public Steering
{
public:
	A3Blend(KinematicUnit* pMover, KinematicUnit* pTarget, bool shouldFlee);
	~A3Blend() { CleanUp(); };

	virtual Steering* getSteering();
	void Init();
	void CleanUp();

private:
	KinematicUnit* mpMover;
	KinematicUnit* mpTarget;

	A3Cohesion* mpCohesion;
	A3GroupAllignment* mpGroupAllignment;
	A3Separation* mpSeparation;
	A3VelocityMatch* mpVelocityMatch;
	A2Wander* mpWander;

	bool mShouldFlee;
};

#endif