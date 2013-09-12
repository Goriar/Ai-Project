#pragma once

#include "steering\Steering.h"

class Character;

// Flee: Calculate the path acceleration in order
// to steer away and escape from a given target
// character (i.e. enemy)
//
class Flee : public PositionSteering {
	
public:
	Flee(Character *target);
	virtual void apply(MoveComponent *);

protected:
	Character *target;
};
