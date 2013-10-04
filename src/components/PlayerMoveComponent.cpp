#include "PlayerMoveComponent.h"
#include "app\globaldefs.h"
#include "components\ItemComponent.h"
#include <GL\glut.h>
#include <string>
#include <sstream>

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
	
	score = 0;
	health = 100.0f;
	attachToCharacter(c);
	active = true;

	playerSize =  c->getSize()/2;
}


PlayerMoveComponent::~PlayerMoveComponent(void)
{
}

void PlayerMoveComponent::update(double deltaTime)
{
	//Prüft die Tastatureingabe und berechnet mit der Beschleunigung die Geschwindigkeit
	determineDirection();
	velocity += deltaTime * accel;
	if (velocity.getLength() > maxVelocity) {
		velocity.normalize();
		velocity *= maxVelocity;
	}

	CVector position = parent->getPosition();

	position += PIXEL_PER_METER *deltaTime * velocity;


	angularVelo += deltaTime * angularAccel;
	if (abs(angularVelo) > maxAngularVelocity) {
		angularVelo = (angularVelo > 0.0)? maxAngularVelocity : - maxAngularVelocity;
	}
	rotation += deltaTime * angularVelo;

	if (rotation > 360.0) rotation  -= 360.0;
	if (rotation < -360.0) rotation += 360.0;

//Prüfen ob der Spieler aus dem Bild laufen würde
	if (position[0] + playerSize > 1024) {
		position[0] = 1024 - playerSize;
		velocity[0] *= -0.2;
	

	}
	if (position[0] < 0 + playerSize) {
		position[0] = 0 + playerSize;
		velocity[0] *= -0.2;
	}
	if (position[1] + playerSize + 20 > 800) {
		position[1] = 800 - playerSize - 20;
		velocity[1] *= -0.2;
	}
	if (position[1] < 0 + playerSize + 10) {
		position[1] = 0 + playerSize + 10;
		velocity[1] *= -0.2;
	}

	parent->setPosition(position);

	//Kollisionsabfrage
	quadColission();
	
	//Prüfen ob der Spieler einen Gegenstand aufnehmen würde
	Character *item = CharacterManager::instance()->getCharacter("Item");
	ItemComponent *itemComp = getComponent<ItemComponent>(item);
	if((item->getPosition()-getPosition()).getLength() < 50.0f){
		itemComp->pickUp();
		score++;
	}
}

//Mittels des Seperating Axis Theorem wird auf eine Kolission mit den Hindernissen geprüft
void PlayerMoveComponent::quadColission()
{

	CVector position = getPosition();
	double size = parent->getSize();

	//Die Eckpunkte des Spielers
	CVector v1 = CVector(position[0]-size,position[1]+size);
	CVector v2 = CVector(position[0]+size,position[1]+size);
	CVector v3 = CVector(position[0]+size,position[1]-size);
	CVector v4 = CVector(position[0]-size,position[1]-size);

	//Die zu prüfenden Achsen werden mit Hilfe der Vektoren der Spielerposition erstellt

	CVector a1 = v1 - v2;
	a1 = CVector(a1[1],-a1[0]);
	a1.normalize();

	CVector a2 = v2 - v3;
	a2 = CVector(a2[1],-a2[0]);
	a2.normalize();

	CVector a3 = v3 - v4;
	a3 = CVector(a3[1],-a3[0]);
	a3.normalize();

	CVector a4 = v4 - v1;
	a4 = CVector(a4[1],-a4[0]);
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

		//Die Eckpunkte eines Obstacles
		CVector w1 = CVector(cPos[0]-cSize,cPos[1]+cSize);
		CVector w2 = CVector(cPos[0]+cSize,cPos[1]+cSize);
		CVector w3 = CVector(cPos[0]+cSize,cPos[1]-cSize);
		CVector w4 = CVector(cPos[0]-cSize,cPos[1]-cSize);

		CVector w[4] = {w1,w2,w3,w4};

		CVector moveVector = CVector(9999999,9999999); 

		//Die Punkte werden auf eine Achse projiziert. Anschließend werden die Maxima und Minima miteinander verglichen
		for(int i = 0; i<4; ++i){
			CVector maxV = CVector();
			CVector minV = CVector();
			CVector	maxW = CVector();
			CVector minW = CVector();

			for(int j = 0; j<4; ++j){

				CVector projV = (a[i] * v[j]) * a[i];
			
				if(projV[0]>maxV[0] || maxV.isNil())
					maxV[0] = projV[0];
				if(projV[1]>maxV[1] || maxV.isNil())
					maxV[1] = projV[1];
				if(projV[0]<minV[0] || minV.isNil())
					minV[0] = projV[0];
				if(projV[1]<minV[1] || minV.isNil())
					minV[1] = projV[1];

				
				CVector projW = (a[i] * w[j]) * a[i];
				if(projW[0]>maxW[0] || maxW.isNil())
					maxW[0] = projW[0];
				if(projW[1]>maxW[1] || maxW.isNil())
					maxW[1] = projW[1];
				if(projW[0]<minW[0] || minW.isNil())
					minW[0] = projW[0];
				if(projW[1]<minW[1] || minW.isNil())
					minW[1] = projW[1];
				
			}

			//Der Vektor in dessen Richtung der Spieler abgestoßen wird,wird berechnet...
			if((maxV[0]>=minW[0] && maxV[1]>=minW[1])&& (minV[0] <= maxW[0] && minV[1] <= maxW[1])){
				CVector vec = (maxV - minW).getLength() < (minV - maxW).getLength() ? maxV-minW : minV - maxW;
				if(moveVector.getLength() > vec.getLength()){
					moveVector = vec;
					
				}
			} else {
				moveVector = CVector();
				break;
			}

		}

		//...und auf die Position des Spielers übertragen
		if(!moveVector.isNil()){
			position-=moveVector;
			moveVector.normalize();
			moveVector *= MAX_VELOCITY/4;
			velocity = -moveVector;
		}

	}
	setPosition(position);
}

void PlayerMoveComponent::determineDirection(){
	//Je nach dem welche Taste eingegeben wurde wird mit maximaler Beschleunigung in die zugwiesene Richtung beschleunigt
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

	//Wenn nichts gedrückt wurde, kommt der Spieler langsam zum stehen
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




