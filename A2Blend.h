#ifndef A2BLEND_H
#define A2BLEND_H

#include "Steering.h"

class KinematicUnit;

class A2Blend : public Steering
{
	public:
		A2Blend(KinematicUnit* pMover, KinematicUnit* pTarget, bool shouldFlee);
		~A2Blend() {};

		virtual Steering* getSteering();
		float getDistance(KinematicUnit* target);

	private:
		KinematicUnit* mpMover;
		KinematicUnit* mpTarget;

		bool mShouldFlee;
};

#endif