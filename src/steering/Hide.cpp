#include "Hide.h"
#include "components\MoveComponent.h"
#include "steering\ObstacleAvoidance.h"

Hide::Hide(CVector pos)
{
	position = pos;
}


Hide::~Hide(void)
{
}

void Hide::apply(MoveComponent *self)
{
	//Steuert so schnell wie möglich einen bestimmten Vektor an
	CVector currentPosition = self->getPosition();
	CVector currentVelocity = self->getVelocity();

	CVector desiredPosition = position;
	CVector desiredVelocity = desiredPosition-currentPosition;

	CVector accel = (desiredVelocity);
	accel.normalize();
	accel *= self->getMaxAccel();

	self->setAccel(accel);

	ObstacleAvoidance::avoideObstacles(self, true);
}

void Hide::retarget(CVector pos)
{
	position = pos;
}
