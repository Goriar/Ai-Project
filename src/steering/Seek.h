#pragma once

#include "steering\Steering.h"

class Character;

// Seek: Calculate the path acceleration in order
// to steer towards a given target character 
//
class Seek : public PositionSteering {
	
public:
	Seek(Character *target);
	virtual void apply(MoveComponent *);
	void retarget(Character *c) { target = c; }

protected:
	Character *target;
};
