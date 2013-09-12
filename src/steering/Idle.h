#pragma once

#include "steering\Steering.h"
#include "mathutil\Vector.h"

class Character;

// Idle: schwebender Geist
class Idle : public PositionSteering {
	
public:
	Idle(CVector p);
	virtual void apply(MoveComponent *);
	virtual void debugDraw(MoveComponent *);

private:
	float peak;
	float actual;
	CVector position;
	bool up;

};