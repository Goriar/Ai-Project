#include "Idle.h"
#include "components\MoveComponent.h"
#include "app\globaldefs.h"
#include <stdlib.h>



Idle::Idle(CVector p) {
	peak = 4.0f;
	actual = 0.1f;
	position = p;
	up = true;
}

void Idle::apply(MoveComponent *self) {

	CVector currentPosition = self->getPosition();

	if( (currentPosition[1] > (position[1]+peak)) && up)
	{
		actual = -0.1f;
		up = false;
		self->setVelocity(CVector(0,0));
	}
	else
	{
		
		if((currentPosition[1] < (position[1]-peak)))
		{
			up = true;
			actual = 0.1f;
			self->setVelocity(CVector(0,0));
		}

	}

	CVector accel = CVector(0,actual);

	accel *= self->getMaxAccel();
	self->setAccel(accel);

}

void Idle::debugDraw(MoveComponent *self) {}