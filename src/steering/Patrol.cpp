#include "Patrol.h"
#include "components\MoveComponent.h"
#include "app\globaldefs.h"


Patrol::Patrol() {
}

// Patrol: patrol a route (left to right, up to down...)
//
void Patrol::apply(MoveComponent *self) {

	CVector currentPosition = self->getPosition();

	self->setAccel(CVector(10.0f,0.0f));


}

void Patrol::debugDraw(MoveComponent *self) {

	// draw the patrol path fpr debuging

	glColor4d(0.2,0.2,0.2,0.5);
	
	CVector startPoint = CVector(10.0f,200.0f);
	CVector endPoint = CVector(10.0f,600.0f);

	glBegin(GL_LINE);

	glVertex2d(startPoint[0],startPoint[1]);
	glVertex2d(endPoint[0],endPoint[1]);

	glEnd();

}