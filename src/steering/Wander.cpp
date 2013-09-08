#include "Wander.h"
#include "components\MoveComponent.h"
#include "app\globaldefs.h"

#define CENTER_OFFSET (100)
#define WANDER_RADIUS (60)
#define MAX_WANDER_VELO (0.1)

Wander::Wander() {
	wanderAngle       = 0.0;
	wanderAngularVelo = 0.1*(2.0f*double(rand())/double(RAND_MAX)-1.0f);
}

// Wander: Move around on a randomized path
//
void Wander::apply(MoveComponent *self) {

	CVector currentPosition = self->getPosition();
	CVector desiredPosition = calculateTargetPosition(self);

	CVector currentVelocity = self->getVelocity();
	CVector desiredVelocity = desiredPosition-currentPosition;

	CVector accel = (desiredVelocity-currentVelocity);
	self->setAccel(accel);

	// move the circle point randomly on the circular path
	// calculate a randomized acceleration for the circle point
	double wanderAngularAccel = (0.2*double(rand())/double(RAND_MAX)-0.1);
	wanderAngularVelo += 0.5*wanderAngularAccel;
	CLAMP(-MAX_WANDER_VELO,wanderAngularVelo,MAX_WANDER_VELO);
	wanderAngle += 0.5*wanderAngularVelo;

}

CVector Wander::calculateCircleCenter(MoveComponent *self) {
	CVector currentPosition = self->getPosition();

	// calculate the direction we're facing from the rotation
	double currentRotation = DEG_TO_RAD(self->getRotation());
	CVector faceDirection = CVector(cos(currentRotation),sin(currentRotation));

	// calculate the center of a circle right in front of you
	return currentPosition + CENTER_OFFSET * faceDirection;
}

CVector Wander::calculateTargetPosition(MoveComponent *self) {

	// calculate the center of a circle right in front of you
	CVector center = calculateCircleCenter(self);

	// calculate the current point on the circle
	double currentRotation = DEG_TO_RAD(self->getRotation());
	double circleAngle = wanderAngle + currentRotation;

	CVector circlePoint = WANDER_RADIUS * CVector(cos(circleAngle),sin(circleAngle));

	// the point on the circle is our desired position
	return center +  circlePoint;

}
void Wander::debugDraw(MoveComponent *self) {

	// draw the circle for debugging
	CVector circleCenter = calculateCircleCenter(self);

	glColor4d(0.2,0.2,0.2,0.5);
	glBegin(GL_LINE_LOOP);
	for(int i = 0; i < 360; i+=10) {
		double angle = DEG_TO_RAD(i);
		CVector v = circleCenter + WANDER_RADIUS * CVector(sin(angle),cos(angle));
		glVertex2d(v[0],v[1]);
	}
	glEnd();

	// draw the target point on the circle
	CVector desiredPosition = calculateTargetPosition(self);
	glPointSize(4.0);
	glColor4d(0.0,0.0,0.0,1.0);
	glBegin(GL_POINTS);
	{
		glVertex2d(desiredPosition[0],desiredPosition[1]);
	}
	glEnd();

}