#pragma once

#include "steering\Steering.h"
#include "mathutil\Vector.h"

class Character;

// Wander: Move around on a randomized path
//
class Wander : public PositionSteering {
	
public:
	Wander();
	virtual void apply(MoveComponent *);
	virtual void debugDraw(MoveComponent *);

private:
	double wanderAngle;
	double wanderAngularVelo;

private:
	CVector calculateCircleCenter(MoveComponent *self);
	CVector calculateTargetPosition(MoveComponent *self);
};
