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

	///////////////////////////////////////////////////////

	// 1. find all near distance obstacles
	Character* ghost = target->getCharacterManager()->getCharacter("Ghost");
	double size = 300.0f;
	// detection box
	double ghostRadius = sqrtf(2* (ghost->getSize()/2)*(ghost->getSize()/2) );
	box_length = MIN_BOX_LENGTH + (self->getVelocity().getLength()/self->getMaxVelocity()) * MIN_BOX_LENGTH;
	vector<Character*> obstacles = target->getCharacterManager()->getAllNearbyCharacters(self->getPosition(), OBSTACLE_TAG, size);

	// iterate over all nearby obstacles
	if(obstacles.size() != 0)
	{
		Character* closestInstersectingObstacle = NULL;
		double distToClosestIP = 99999999;
		CVector localPosOfClosestObstacle;

		double obstacleRadius;

		vector<Character *>::iterator it = obstacles.begin();
	
		while(it != obstacles.end())
		{
			Character *c = (*it);
			// calculate obstacle position in local space
			CVector localPos = CVector(self->getPosition()[0] - c->getPosition()[0], self->getPosition()[1] - c->getPosition()[1] );
			obstacleRadius = sqrtf(2*  (c->getSize()/2)*(c->getSize()/2)) + 30;

	
				glColor4d(0.0,1.0,0.2,1.0);
				glBegin(GL_LINE_LOOP);
				for(int i = 0; i < 360; i+=10) {
					double angle = DEG_TO_RAD(i);
					CVector v = c->getPosition() + obstacleRadius * CVector(sin(angle),cos(angle));
					glVertex2d(v[0],v[1]);
				}
				glEnd();


			if(localPos[0] >= 0)
			{
				double expandedRadius = obstacleRadius + ghostRadius;
				
				if(abs(localPos[0]) < expandedRadius)
				{
					// potential intersection, now do a line-circle intersection test
					// circle cX, cY
					// intersection points x = cX +/- sqrt(r^2 - cY^2) for y = 0
					double cX = localPos[0];
					double cY = localPos[1];

					double sqrtPart = sqrt(expandedRadius * expandedRadius - cY*cY);

					double ip = cX - sqrtPart;

					if(ip <= 0)
					{
						ip = cX + sqrtPart;
					}

					if(ip < distToClosestIP)
					{
						closestInstersectingObstacle = c;
						localPosOfClosestObstacle = localPos;
					}
				}
			}
			++it;
		}

		// found one, now calculate the steering force (breaking force and lateral force)
		if(closestInstersectingObstacle != NULL)
		{
			cout << "nearest: " << closestInstersectingObstacle->getName() << endl;
			CVector steeringAcceleration;
			
			double multiplier = 1.0 + (box_length - localPosOfClosestObstacle[0]) / box_length;

			// lateral force
			steeringAcceleration[1] = (obstacleRadius - localPosOfClosestObstacle[1]) * multiplier;

			// breaking force
			const double breakingWeight = 0.2f;

			steeringAcceleration[0] = (obstacleRadius - localPosOfClosestObstacle[0]) * breakingWeight;

			// set acceleration
			CVector worldAcc = CVector( closestInstersectingObstacle->getPosition()[0] + steeringAcceleration[0], closestInstersectingObstacle->getPosition()[1] + steeringAcceleration[1]);
			self->setAccel( worldAcc );

			// distance between ghost and nearest intersection obstacle
			//CVector dist = self->getPosition() - closestInstersectingObstacle->getPosition();

			//CVector normal = CVector(0.0, 1.0);
			//// R = 2 * N * dot(N, OV) - OV
			//CVector reflection = 2 * normal * (normal[0]*dist[0] + normal[1]*dist[1]) - dist;
			////cout << dist.getLength() - obstacleRadius - ghostRadius << endl;
		
			//printf("dist: x%f y%f ----- ref: x%f y%f\n", dist[0], dist[1], reflection[0], reflection[1]);

			//self->setAccel(reflection);
		}

	}
}

void ObstacleAvoidance::debugDraw(MoveComponent *mc)
{
	double box_length = MIN_BOX_LENGTH + (mc->getVelocity().getLength()/mc->getMaxVelocity()) * MIN_BOX_LENGTH;

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

	glPopMatrix();

}