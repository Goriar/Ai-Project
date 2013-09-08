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
	fov = mousePosition - parent->getPosition();
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
	glColor3f(1.0,1.0,1.0);

	CVector position = parent->getPosition();
	double rotation = parent->getRotation();
	

		double scale = MAX_VIEW_FIELD_LENGTH/fov.getLength();
		fov = fov*scale;
	
		CVector v1 = fov - CVector(-fov[1],fov[0])*M_PI/6;
		CVector v2 = fov - CVector(fov[1],-fov[0])*M_PI/6;

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glTranslated(position[0],position[1],0.0);
	glDisable(GL_TEXTURE_2D);

	glColor3f(1.0,0.0,0.0);
	glDisable(GL_TEXTURE_2D);
	glBegin(GL_TRIANGLES);
	glVertex2d(0.0,0.0);
	glVertex2d(v1[0],v1[1]);
	glVertex2d(v2[0],v2[1]);
	glEnd();

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

void PlayerMoveComponent::setMousePosition(CVector mouse){
	mousePosition = mouse;
}

bool PlayerMoveComponent::pointInView(CVector p){
	CVector3 point = CVector3(p[0],p[1],0.0);

	CVector v1 = fov - CVector(-fov[1],fov[0])*M_PI/6;
	CVector v2 = fov - CVector(fov[1],-fov[0])*M_PI/6;
	CVector position = parent->getPosition();

	CVector3 a = CVector3(v1[0],v1[1],0.0);
	CVector3 b = CVector3(v2[0],v2[1],0.0);
	CVector3 c = CVector3(position[0],position[1],0.0);

	if(edgeSideTest(point,a,b,c) && edgeSideTest(point,b,a,c) && edgeSideTest(point,c,a,b))
		return true;
	else 
		return false;
}

bool PlayerMoveComponent::edgeSideTest(CVector3 p1,CVector3 p2, CVector3 a, CVector3 b){
	CVector3 cp1 = cp1.crossProduct(b-a,p1-a);
	CVector3 cp2 = cp1.crossProduct(b-a,p2-a);
	if(cp1*cp2 >= EPSILON)
		return true;
	else
		return false;
}


