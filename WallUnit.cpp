#include "WallUnit.h"
#include "Game.h"
#include "GraphicsSystem.h"

WallUnit::WallUnit(Vector2D topLeft, Vector2D bottomRight)
:Kinematic(topLeft, 0, 0, 0) // initializing velocity, orientation, and rotational velocity as 0
{
	mTopLeft = topLeft;
	mBottomRight = bottomRight;

	mTopRight.setX(mTopLeft.getX());
	mTopRight.setY(mBottomRight.getY());

	mBottomLeft.setX(mBottomRight.getX());
	mBottomLeft.setY(mTopLeft.getY());
}

WallUnit::~WallUnit()
{

}

void WallUnit::draw()
{
	GET_GAME->getGraphicsSystem()->drawRectangle(mTopLeft, mBottomRight);
}