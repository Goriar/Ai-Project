#define USE_MATH_DEFINES
#include <math.h>

#include "LookWhereYoureGoing.h"
#include "components\MoveComponent.h"
#include "app\globaldefs.h"
#include <stdio.h>

// Look Where You're Going: Adjust the rotation 
// of the character to face along the path it 
// is moving
//
void LookWhereYoureGoing::apply(MoveComponent *self) {
	
	CVector currentVelocity = self->getVelocity();

	if (currentVelocity.getLength() < EPSILON) {
		// if we're not moving, no angular 
		// acceleration is necessary
		self->setAngularAccel(0.0);
		return;
	}

	// calculate the rotation angle (polar coordinates)
	double angle = RAD_TO_DEG(atan2(currentVelocity[1],currentVelocity[0]));

	// set the rotation
	self->setRotation(angle);

	// clear angular velocity and acceleration
	self->setAngularVelocity(0.0);
	self->setAngularAccel(0.0);
	
}