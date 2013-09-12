#include "Flee.h"
#include "core\Character.h"
#include "app\globaldefs.h"
#include "components\MoveComponent.h"


Flee::Flee(Character *target)  {
	this->target = target;
}

// Flee: Calculate the path acceleration in order
// to steer away and escape from a given target
// character (i.e. enemy)
//
void Flee::apply(MoveComponent *self) {

	CVector currentPosition = self->getPosition();
	CVector currentVelocity = self->getVelocity();

	CVector enemyPosition   = target->getPosition();
	CVector desiredVelocity = currentPosition - enemyPosition;

	// move away from enemy with maximum velocity
	CVector accel = (desiredVelocity - currentVelocity);
	accel.normalize();
	accel *= self->getMaxAccel();

	self->setAccel(accel);


}