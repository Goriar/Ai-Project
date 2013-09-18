#include "Hide.h"
#include "components\MoveComponent.h"


Hide::Hide(CVector pos)
{
	position = pos;
}


Hide::~Hide(void)
{
}

void Hide::apply(MoveComponent *self)
{
	CVector currentPosition = self->getPosition();
	CVector currentVelocity = self->getVelocity();

	CVector desiredPosition = position;
	CVector desiredVelocity = desiredPosition-currentPosition;

	CVector accel = (desiredVelocity-currentVelocity);
	accel.normalize();
	accel *= self->getMaxAccel();

	self->setAccel(accel);
}

void Hide::retarget(CVector pos)
{
	position = pos;
}
