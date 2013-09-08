#pragma once

#include "steering\Steering.h"

class Character;

// Look Where You're Going: Adjust the rotation 
// of the character to face along the path it 
// is moving
//
class LookWhereYoureGoing : public AngularSteering {
	
public:
	virtual void apply(MoveComponent *);

};
