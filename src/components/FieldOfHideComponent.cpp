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
		
	foh = (-1)*(player->getPosition() - parent->getPosition());
	double scale = MAX_HIDE_FIELD_LENGTH/foh.getLength();
	foh = foh*scale;
	
}
void FieldOfHideComponent::draw() {
	glColor3f(1.0,1.0,1.0);

	CVector position = parent->getPosition();
	double rotation = parent->getRotation();
	
	CVector v1 = foh - CVector(-foh[1],foh[0])*M_PI/6;
	CVector v2 = foh - CVector(foh[1],-foh[0])*M_PI/6;

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glTranslated(position[0],position[1],0.0);

	glColor3f(0.0,1.0,0.0);
	glDisable(GL_TEXTURE_2D);
	glBegin(GL_TRIANGLES);
	glVertex2d(0.0,0.0);
	glVertex2d(v1[0],v1[1]);
	glVertex2d(v2[0],v2[1]);
	glEnd();

	glPopMatrix();

	glColor4d(1.0,1.0,1.0,1.0);
}