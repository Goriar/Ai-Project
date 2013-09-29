#include "Seek.h"
#include "core\Character.h"
#include "app\globaldefs.h"
#include "components\MoveComponent.h"

#include "steering\Wander.h"
#include "steering\Idle.h"
#include "steering\Patrol.h"
#include "steering\ObstacleAvoidance.h"

#include "assert.h"

Seek::Seek(Character *target) {
	this->target = target;
}

// Seek: Calculate the path acceleration in order
// to steer towards a given target character 
//
void Seek::apply(MoveComponent *self) {

	CVector currentPosition = self->getPosition();
	CVector currentVelocity = self->getVelocity();

	CVector desiredPosition = target->getPosition();
	CVector desiredVelocity = desiredPosition-currentPosition;
	
	CVector accel = (desiredVelocity);
	accel.normalize();
	accel *= self->getMaxAccel();

	self->setAccel(accel);

	ObstacleAvoidance::avoideObstacles(self, false);
}

void Seek::debugDraw(MoveComponent *mc)
{
}