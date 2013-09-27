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
	
	v1 = foh - CVector(-foh[1],foh[0])*M_PI/3;
	v2 = foh - CVector(foh[1],-foh[0])*M_PI/3;
	v3;
	v4;

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

///////// GHOSTS ARE INVISIBLE IN FOH ---> BUG? /////////
//bool FieldOfHideComponent::ghostInPolygon(CVector ve1, CVector ve2, CVector ve3, CVector ve4) {
//	if (pointInPolygon(ve1, v1, v2) && pointInPolygon(ve1, v2, v3) && pointInPolygon(ve1, v3, v4) && pointInPolygon(ve1, v4, v1) &&
//		pointInPolygon(ve2, v1, v2) && pointInPolygon(ve2, v2, v3) && pointInPolygon(ve2, v3, v4) && pointInPolygon(ve2, v4, v1) &&
//		pointInPolygon(ve3, v1, v2) && pointInPolygon(ve3, v2, v3) && pointInPolygon(ve3, v3, v4) && pointInPolygon(ve3, v4, v1) &&
//		pointInPolygon(ve4, v1, v2) && pointInPolygon(ve4, v2, v3) && pointInPolygon(ve4, v3, v4) && pointInPolygon(ve4, v4, v1)) {
//			return true;}
//	return false;
//}
//bool FieldOfHideComponent::pointInPolygon(CVector v, CVector s, CVector e) {
//	if (v[1] == s[1] == e[1]) return true;
//	if (s[1] > e[1]) {
//		float tmp = s[1];
//		float tmp2 = s[0];
//		s[1] = e[1];
//		s[0] = e[0];
//		e[1] = tmp;
//		e[0] = tmp2;}
//	if (v[0] == s[0] && v[1] == s[1]) return true;
//	if (v[0] == e[0] && v[1] == e[1]) return true;
//	if (v[1] <= s[1] || v[1] >= e[1]) return true;
//	float tmp = (s[0]-v[0])*(e[1]-v[1])-(s[1]-v[1])*(e[0]-v[0]);
//	if (tmp <= 0) return true;
//	return false;
//}