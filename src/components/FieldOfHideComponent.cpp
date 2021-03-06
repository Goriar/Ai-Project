#include "FieldOfHideComponent.h"


FieldOfHideComponent::FieldOfHideComponent(Character *p, CharacterManager *cm, Character *c) {
	parent = NULL;
	attachToCharacter(c);
	player = p;
	foh = CVector(0,0);
	characterManager = cm;
	active = true;
}


FieldOfHideComponent::~FieldOfHideComponent(void) {
}

void FieldOfHideComponent::update(double deltaTime) {
	//Scale Field of Hide	
	foh = (-1)*(player->getPosition() - parent->getPosition());
	double scale = MAX_HIDE_FIELD_LENGTH/foh.getLength();
	foh = foh*scale;
}

void FieldOfHideComponent::draw() {

	glColor3f(1.0,1.0,1.0);

	CVector position = parent->getPosition();
	double rotation = parent->getRotation();
	//calculate vectors
	v1 = foh - CVector(-foh[1],foh[0])*M_PI/3;
	v2 = foh - CVector(foh[1],-foh[0])*M_PI/3;
	v3;
	v4;
	//calculate vectors on the Edges of the Obstacle
	if (player->getPosition()[1] >= parent->getPosition()[1]+parent->getSize()) {
		if (player->getPosition()[0] >= parent->getPosition()[0]+parent->getSize()) {
			v3[0] = 0.0+parent->getSize();
			v3[1] = 0.0-parent->getSize();
			v4[0] = 0.0-parent->getSize();
			v4[1] = 0.0+parent->getSize();
		} else if (player->getPosition()[0] <= parent->getPosition()[0]-parent->getSize()) {
			v3[0] = 0.0+parent->getSize();
			v3[1] = 0.0+parent->getSize();
			v4[0] = 0.0-parent->getSize();
			v4[1] = 0.0-parent->getSize();
		} else {
			v3[0] = 0.0+parent->getSize();
			v3[1] = 0.0+parent->getSize();
			v4[0] = 0.0-parent->getSize();
			v4[1] = 0.0+parent->getSize();
		}
	} else if (player->getPosition()[1] <= parent->getPosition()[1]-parent->getSize()) {
		if (player->getPosition()[0] >= parent->getPosition()[0]+parent->getSize()) {
			v3[0] = 0.0-parent->getSize();
			v3[1] = 0.0-parent->getSize();
			v4[0] = 0.0+parent->getSize();
			v4[1] = 0.0+parent->getSize();
		} else if (player->getPosition()[0] <= parent->getPosition()[0]-parent->getSize()) {
			v3[0] = 0.0-parent->getSize();
			v3[1] = 0.0+parent->getSize();
			v4[0] = 0.0+parent->getSize();
			v4[1] = 0.0-parent->getSize();
		} else {
			v3[0] = 0.0-parent->getSize();
			v3[1] = 0.0-parent->getSize();
			v4[0] = 0.0+parent->getSize();
			v4[1] = 0.0-parent->getSize();
		}
	} else {
		if (player->getPosition()[0] >= parent->getPosition()[0]+parent->getSize()) {
			v3[0] = 0.0+parent->getSize();
			v3[1] = 0.0-parent->getSize();
			v4[0] = 0.0+parent->getSize();
			v4[1] = 0.0+parent->getSize();
		} else if (player->getPosition()[0] <= parent->getPosition()[0]-parent->getSize()) {
			v3[0] = 0.0-parent->getSize();
			v3[1] = 0.0+parent->getSize();
			v4[0] = 0.0-parent->getSize();
			v4[1] = 0.0-parent->getSize();
		} else {
			//should never happen
			v3[0] = 0.0;
			v3[1] = 0.0;
			v4[0] = 0.0;
			v4[1] = 0.0;
			std::cout << "You are in the Obstacle" << endl;
		}
	}

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glTranslated(position[0],position[1],0.0);

	if(debug)
	{
		glColor3f(0.0,1.0,0.0);
	}
	else
	{
		glColor3f(0.0,0.0,0.0);
	}
	//Draw Polygon
	glDisable(GL_TEXTURE_2D);
	glBegin(GL_POLYGON);
	glVertex2d(v3[0],v3[1]);
	glVertex2d(v4[0],v4[1]);
	glVertex2d(v1[0],v1[1]);
	glVertex2d(v2[0],v2[1]);
	glEnd();

	glPopMatrix();

	glColor4d(1.0,1.0,1.0,1.0);
	
}

CVector FieldOfHideComponent::getCenterPosition()
{
	CVector vec = foh + parent->getPosition();

	return vec;
}