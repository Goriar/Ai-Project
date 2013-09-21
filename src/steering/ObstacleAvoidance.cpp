#include "ObstacleAvoidance.h"
#include "core\Character.h"
#include "app\globaldefs.h"
#include "components\MoveComponent.h"

#define MIN_BOX_LENGTH (100)

ObstacleAvoidance::ObstacleAvoidance(Character *target) {
	box_length = 0.0f;
	this->target = target;
}

void ObstacleAvoidance::apply(MoveComponent *self) {

	//////////////////SEEK BEHAVIOUR/////////////////////////

	CVector currentPosition = self->getPosition();
	CVector currentVelocity = self->getVelocity();

	CVector desiredPosition = target->getPosition();
	CVector desiredVelocity = desiredPosition-currentPosition;
	
	CVector accel = (desiredVelocity-currentVelocity);
	accel.normalize();
	accel *= self->getMaxAccel();

	self->setAccel(accel);

}

void ObstacleAvoidance::avoideObstacles(MoveComponent *self)
{
	const float MAX_LOOK_AHEAD = 100;
	const float NEARBY_OBSTACLE_DISTANCE = 300.0f;
	const float MAX_AVOIDANCE_FORCE = 2000.0f;

	//cout << "v: " << self->getVelocity().getLength() << endl;

	CVector velocity = self->getVelocity();
	CVector ghostPosition = self->getPosition();
	double dynamic_length = velocity.getLength() / MAX_VELOCITY * MAX_LOOK_AHEAD;
	velocity.normalize();

	CVector ahead = ghostPosition + velocity * dynamic_length;
	CVector ahead2 = ahead * 0.5;

	// draw look ahead vector
	if (debug) {
		glColor3f(0.0, 1.0, 0.0);
		glBegin(GL_LINE_STRIP);
			glVertex2d( ghostPosition[0], ghostPosition[1] );
			glVertex2d( ahead[0], ahead[1] );
		glEnd();
	}
	
	// find obstacles in near distance
	CharacterManager* cm = CharacterManager::instance();
	vector<Character*> obstacles = cm->getAllNearbyCharacters(self->getPosition(), OBSTACLE_TAG, NEARBY_OBSTACLE_DISTANCE);

	if(obstacles.size() != 0)
	{
		Character* closestInstersectingObstacle = NULL;
		double distToClosestObstacle = 99999999;

		vector<Character *>::iterator it = obstacles.begin();
	
		while(it != obstacles.end())
		{
			// find the nearest obstacle
			Character *c = (*it);
			
			if( (c->getPosition() - ghostPosition).getLength() < distToClosestObstacle)
			{
				distToClosestObstacle = (c->getPosition() - ghostPosition).getLength();
				closestInstersectingObstacle = c;
			}
			++it;
		}

		if(closestInstersectingObstacle != NULL)
		{
			// check if the line and circle intesect
			double obstacleRadius = sqrtf(2*  (closestInstersectingObstacle->getSize()/2)*(closestInstersectingObstacle->getSize()/2)) + 20;
			if (debug) {
				glColor4d(0.0,1.0,0.2,1.0);
				glBegin(GL_LINE_LOOP);
				for(int i = 0; i < 360; i+=10) {
					double angle = DEG_TO_RAD(i);
					CVector v = closestInstersectingObstacle->getPosition() + obstacleRadius * CVector(sin(angle),cos(angle));
					glVertex2d(v[0],v[1]);
				}
				glEnd();
			}


			// if vector ahead or ahead2 distance to the circle center is lesser than the radius -> collision
			if( (closestInstersectingObstacle->getPosition() - ahead).getLength() <= obstacleRadius || (closestInstersectingObstacle->getPosition() - ahead2).getLength() <= obstacleRadius 
				|| (closestInstersectingObstacle->getPosition() - ghostPosition).getLength() <= obstacleRadius )
			{
				// calculate acceleration
				CVector avoidance_force = ahead - closestInstersectingObstacle->getPosition();
				avoidance_force.normalize();
				avoidance_force*= MAX_AVOIDANCE_FORCE;

				self->setAccel(avoidance_force);
			}
		}
	}
}

void ObstacleAvoidance::debugDraw(MoveComponent *mc)
{
	/*double box_length = MIN_BOX_LENGTH + (mc->getVelocity().getLength()/mc->getMaxVelocity()) * MIN_BOX_LENGTH;

	CVector pos = mc->getPosition();

	double r = 20.0f;
	double rot = DEG_TO_RAD(mc->getRotation());
	double x1 = 0.0f * cosf(rot) - r * sinf(rot);
	double y1 = r * cosf(rot) + 0.0f * sinf(rot);

	double x2 = 0.0f * cosf(rot) - (-r) * sinf(rot);
	double y2 = -r * cosf(rot) + 0.0f * sinf(rot);

	CVector velocity = mc->getVelocity();
	//velocity[0] += min_box_length;
	//velocity[1] += min_box_length;

	// draw rectangle 
	glColor3f(0.0,0.0,0.0);


	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glTranslated(pos[0],pos[1],0.0);
	glDisable(GL_TEXTURE_2D);

	glBegin(GL_LINE_STRIP);
		glVertex2d( x1, y1 );
		glVertex2d( x1 + velocity[0], y1 + velocity[1]);
		glVertex2d( x2 + velocity[0], y2 + velocity[1]);
		glVertex2d( x2, y2);
	glEnd();

	glPopMatrix();*/

}