#include "Seek.h"
#include "core\Character.h"
#include "app\globaldefs.h"
#include "components\MoveComponent.h"

#include "steering\Wander.h";
#include "steering\Idle.h"
#include "steering\Patrol.h"

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
	
	//cout << "length: " << desiredVelocity.getLength() << endl;
	//if(desiredVelocity.getLength() <=  GHOST_PLAYER_DIST)
	//{// ändere Verhalten
	//	self->setVelocity(CVector(0.0f,0.0f));
	//	self->setAccel(CVector(0.0f,0.0f));
	//	self->setPositionSteering(new Idle(self->getPosition()));
	//	
	//	return;
	//}
	// move with maximum acceleration
	CVector accel = (desiredVelocity-currentVelocity);
	accel.normalize();
	accel *= self->getMaxAccel();

	self->setAccel(accel);

}

void Seek::debugDraw(MoveComponent *mc)
{
}