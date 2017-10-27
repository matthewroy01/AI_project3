#ifndef WALLUNIT_H
#define WALLUNIT_H

#include "Kinematic.h"

class GraphicsBuffer;

class WallUnit : public Kinematic
{
	public:
		WallUnit(Vector2D topLeft, Vector2D bottomRight);
		~WallUnit();

		void draw();

	private:
		Vector2D mTopLeft, mTopRight, mBottomLeft, mBottomRight;
};

#endif
