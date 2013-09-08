#pragma once

#include "steering\Steering.h"
#include "mathutil\Vector.h"

class Character;

// Patrol: patrol a route (left to right, up to down...)
//
class Patrol : public PositionSteering {
	
public:
	Patrol();
	virtual void apply(MoveComponent *);
	virtual void debugDraw(MoveComponent *);

private:
	int patrol_mode;

};