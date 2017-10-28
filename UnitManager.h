#ifndef UNITMANAGER_H
#define UNITMANAGER_H

#include <vector>
#include "Trackable.h"

class Kinematic;
class KinematicUnit;
class WallUnit;
class GraphicsBuffer;

class UnitManager : public Trackable
{
	private :
		// constants for changing values in modes
		const int ALL_VELOCITY_CONST = 20;
		const float ALL_ANGULAR_CONST = 0.25f;
		const int ALL_RADIUS_CONST = 20;

		// a vector of all the units in the scene
		std::vector <KinematicUnit*> mpUnits;
		std::vector <WallUnit*> mpWalls;

		enum Mode { vel = 0, rad, ang };
		Mode mCurrentMode;

		// for changing modes, all of these variables will be consistent between all units
		float mAllMaxVelocity, mAllRadius, mAllAngularVelocity;

	public :
		UnitManager();
		~UnitManager();

		void AddUnit(KinematicUnit* uni, int AItype);
		void AddWallUnit(WallUnit* uni);
		void RemoveRandomUnit();
		KinematicUnit* GetUnit(int id);
		WallUnit* GetWall(int id);

		void ChangeCurrentMode(int mode);
		int GetCurrentMode();

		void UnitUpdate(float t);
		void UnitDraw(GraphicsBuffer* buffer);

		// accessors and mutators for mode values
		void changeAllVelocity(bool add);
		void changeAllAngular(bool add);
		void changeAllRadius(bool add);

		float getAllVelocity() { return mAllMaxVelocity; };
		float getAllAngular() { return mAllAngularVelocity; };
		float getAllRadius() { return mAllRadius; };

		int getNumberOfUnits() { return mpUnits.size(); };
		int getNumberOfWalls() { return mpWalls.size(); };
};

#endif