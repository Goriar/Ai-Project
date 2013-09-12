#include "PlayerMoveComponent.h"
#include "app\globaldefs.h"

PlayerMoveComponent::PlayerMoveComponent(bool *keys,Character *c)
{
	parent = NULL;
	
	velocity.set(0.0,0.0);
	accel.set(0.0,0.0);
	angularVelo = 0.0;
	angularAccel = 0.0;

	keyStates = keys;

	// init default maxima
	maxVelocity        = MAX_VELOCITY;
	maxAccel           = MAX_ACCEL;
	maxAngularVelocity = MAX_ANGULAR_VELOCITY;
	maxAngularAccel    = MAX_ANGULAR_ACCEL;
	
	attachToCharacter(c);
	active = true;
}


PlayerMoveComponent::~PlayerMoveComponent(void)
{
}

void PlayerMoveComponent::update(double deltaTime)
{
	determineDirection();
	velocity += deltaTime * accel;
	if (velocity.getLength() > maxVelocity) {
		velocity.normalize();
		velocity *= maxVelocity;
	}

	CVector position = parent->getPosition();
	double rotation = parent->getRotation();

	position += PIXEL_PER_METER *deltaTime * velocity;

	angularVelo += deltaTime * angularAccel;
	if (abs(angularVelo) > maxAngularVelocity) {
		angularVelo = (angularVelo > 0.0)? maxAngularVelocity : - maxAngularVelocity;
	}
	rotation += deltaTime * angularVelo;

	if (rotation > 360.0) rotation  -= 360.0;
	if (rotation < -360.0) rotation += 360.0;

	if (position[0] > 1024) {
		position[0] = 1024;
		velocity[0] *= -1.0;
	}
	if (position[0] < 0) {
		position[0] = 0;
		velocity[0] *= -1.0;
	}
	if (position[1] > 800) {
		position[1] = 800;
		velocity[1] *= -1.0;
	}
	if (position[1] < 0) {
		position[1] = 0;
		velocity[1] *= -1.0;
	}

	parent->setPosition(position);
	parent->setRotation(rotation);

	quadColission();
}

void PlayerMoveComponent::quadColission()
{
	CVector position = getPosition();
	double size = parent->getSize();

	CVector v1 = CVector(position[0]-size,position[1]+size);
	CVector v2 = CVector(position[0]+size,position[1]+size);
	CVector v3 = CVector(position[0]+size,position[1]-size);
	CVector v4 = CVector(position[0]-size,position[1]-size);


	CVector a1 = v1 - v2;
	a1 = CVector(-a1[1],a1[0]);
	a1.normalize();

	CVector a2 = v2 - v3;
	a2 = CVector(-a2[1],a2[0]);
	a2.normalize();

	CVector a3 = v3 - v4;
	a3 = CVector(-a3[1],a3[0]);
	a3.normalize();

	CVector a4 = v4 - v1;
	a4 = CVector(-a4[1],a4[0]);
	a4.normalize();

	CVector a[4] = {a1,a2,a3,a4};
	CVector v[4] = {CVector(-size,size),CVector(size,size),CVector(size,-size),CVector(-size,-size)};

	vector<Character *> characters = parent->getCharacterManager()->getAllNearbyCharacters(getPosition(),OBSTACLE_TAG,200.0);

	vector<Character *>::iterator it = characters.begin();

	while(it != characters.end())
	{
		Character *c = (*it);
		it++;

		CVector cPos = c->getPosition()-position;
		double cSize = c->getSize();

	
		CVector w1 = CVector(cPos[0]-cSize,cPos[1]+cSize);
		CVector w2 = CVector(cPos[0]+cSize,cPos[1]+cSize);
		CVector w3 = CVector(cPos[0]+cSize,cPos[1]-cSize);
		CVector w4 = CVector(cPos[0]-cSize,cPos[1]-cSize);

		CVector w[4] = {w1,w2,w3,w4};

		CVector moveVector = CVector(9999999,9999999); 

		for(int i = 0; i<4; ++i){
			CVector maxV = CVector(0,0);
			CVector minV = CVector(9999999,9999999);
			CVector	maxW = CVector(0,0);
			CVector minW = CVector(9999999,9999999);

			for(int j = 0; j<4; ++j){

				CVector projV = (a[i] * v[j]) * a[i];
				if(projV.getLength()>maxV.getLength())
					maxV = projV;
				if(projV.getLength()<minV.getLength())
					minV = projV;

				
				CVector projW = (a[i] * w[j]) * a[i];
				if(projW.getLength()>maxW.getLength())
					maxW = projW;
				if(projW.getLength()<minW.getLength())
					minW = projW;

				
			}

			if(maxV.getLength()>minW.getLength() && minV.getLength() < maxW.getLength()){
				CVector a = (maxV - minW).getLength() < (minV - maxW).getLength() ? maxV-minW : minV - maxW;
				if(moveVector.getLength() > a.getLength()){
					moveVector = a;
				}
			} else {
				moveVector = CVector();
				
			}

		}

		if(!moveVector.isNil()){
			std::cout << moveVector[0] << " " << moveVector[1] << endl;
			position-=moveVector*1.2;
			moveVector.normalize();
			moveVector *= MAX_VELOCITY;
			velocity = -moveVector;
		}

	}
	setPosition(position);
}

void PlayerMoveComponent::determineDirection(){
	
	if(keyStates['w'] || keyStates['W']){
		if(keyStates['a'] || keyStates['A'])
			setAccel(CVector(-MAX_ACCEL,MAX_ACCEL));
		else if(keyStates['d'] || keyStates['D'])
			setAccel(CVector(MAX_ACCEL,MAX_ACCEL));
		else setAccel(CVector(0.0,MAX_ACCEL));
		return;
	}

	if(keyStates['a'] || keyStates['A']){
		if(keyStates['w'] || keyStates['W'])
			setAccel(CVector(-MAX_ACCEL,MAX_ACCEL));
		else if(keyStates['s'] || keyStates['S'])
			setAccel(CVector(-MAX_ACCEL,-MAX_ACCEL));
		else setAccel(CVector(-MAX_ACCEL,0));
		return;
	}

	if(keyStates['s'] || keyStates['S']){
		if(keyStates['d'] || keyStates['D'])
			setAccel(CVector(MAX_ACCEL,-MAX_ACCEL));
		else if(keyStates['a'] || keyStates['A'])
			setAccel(CVector(-MAX_ACCEL,-MAX_ACCEL));
		else setAccel(CVector(0,-MAX_ACCEL));
		return;
	}

	if(keyStates['d'] || keyStates['D']){
		if(keyStates['s'] || keyStates['S'])
			setAccel(CVector(MAX_ACCEL,-MAX_ACCEL));
		else if(keyStates['w'] || keyStates['W'])
			setAccel(CVector(MAX_ACCEL,MAX_ACCEL));
		else setAccel(CVector(MAX_ACCEL,0));
		return;
	}

	if(velocity!=CVector(0,0)){
		float x = 0.0;
		float y = 0.0;
		if(velocity[0]>0)
			x = -MAX_ACCEL;
		else
			x = MAX_ACCEL;

		if(velocity[1]>0)
			y = -MAX_ACCEL;
		else
			y = MAX_ACCEL;
		setAccel(CVector(x,y));
	}
}

void PlayerMoveComponent::draw()
{
	/*
	glColor3f(1.0,1.0,1.0);

	CVector position = parent->getPosition();
	double rotation = parent->getRotation();

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glTranslated(position[0],position[1],0.0);
	glDisable(GL_TEXTURE_2D);

	glColor3f(1.0,0.0,0.0);
	glDisable(GL_TEXTURE_2D);
	glBegin(GL_LINES);
	glVertex2d(0.0,0.0);
	glVertex2d(velocity[0],velocity[1]);
	glEnd();

	glColor3f(0.0,0.0,1.0);
	glDisable(GL_TEXTURE_2D);
	glBegin(GL_LINES);
	glVertex2d(0.0,0.0);
	glVertex2d(accel[0],accel[1]);
	glEnd();

	glPopMatrix();

	glColor4d(1.0,1.0,1.0,1.0);
	*/
}

void PlayerMoveComponent::setPosition(const CVector &vec)
{
	parent->setPosition(vec);
}

void PlayerMoveComponent::setRotation(double v)
{
	parent->setRotation(v);
}

void PlayerMoveComponent::setVelocity(const CVector &vec)
{
	velocity = vec;
}

void PlayerMoveComponent::setAccel(const CVector &vec)
{
	accel = vec;
}

void PlayerMoveComponent::setAngularVelocity(double v)
{
	angularVelo = v;
}

void PlayerMoveComponent::setAngularAccel(double v)
{
	angularAccel = v;
}




