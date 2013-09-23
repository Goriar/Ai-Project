#include "FieldOfViewComponent.h"
#include "components\GhostBehaviourComponent.h"


FieldOfViewComponent::FieldOfViewComponent(CVector* mouse, Character *c)
{
	parent = NULL;
	attachToCharacter(c);
	mousePosition = mouse;
	fov = CVector(0,0);
	active = true;
	seenEnemies.clear();
}


FieldOfViewComponent::~FieldOfViewComponent(void)
{
}

void FieldOfViewComponent::update(double deltaTime)
{
	
	fov = *mousePosition - parent->getPosition();
	double scale = MAX_VIEW_FIELD_LENGTH/fov.getLength();
	fov = fov*scale;
	vector<Character *> nearbyCharacters = parent->getCharacterManager()->getAllNearbyCharacters(parent->getPosition(),GHOST_TAG,MAX_VIEW_FIELD_LENGTH+50.0);

	vector<Character *>::iterator it = nearbyCharacters.begin();

	seenEnemies.clear();
	while(it!=nearbyCharacters.end()){
		Character *c = (*it);
		it++;
		double size = c->getSize();
		CVector p = c->getPosition() - parent->getPosition();
		CVector v1 = CVector(p[0]-size,p[1]+size);
		CVector v2 = CVector(p[0]+size,p[1]+size);
		CVector v3 = CVector(p[0]-size,p[1]-size);
		CVector v4 = CVector(p[0]+size,p[1]-size);

		if(pointInView(v1)||pointInView(v2)||pointInView(v3)||pointInView(v4)){
			// BENACHRICHTIGUNG AN GEISTER EINFÜGEN
			seenEnemies.push_back(c);
			// finde ghost behaviour komponente
			vector<Component *> compVec = c->attachedComponents();
			vector<Component *>::iterator it2 = compVec.begin();

			while(it2 != compVec.end())
			{
				Component *comp = (*it2);
				it2++;

				if(comp->getTag() == GHOST_BEH)
					((GhostBehaviourComponent*) comp)->setState(FLEE);
			}

			//std::cout << "I SEE YOU!" << endl;
		}
	}
	
}
void FieldOfViewComponent::draw()
{
	glColor3f(1.0,1.0,1.0);

	CVector position = parent->getPosition();
	double rotation = parent->getRotation();
	
	CVector v1 = fov - CVector(-fov[1],fov[0])*M_PI/6;
	CVector v2 = fov - CVector(fov[1],-fov[0])*M_PI/6;

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glTranslated(position[0],position[1],0.0);

	glColor3f(1.0,1.0,1.0);
	glDisable(GL_TEXTURE_2D);
	glBegin(GL_TRIANGLES);
	glVertex3d(0.0,0.0, DRAW_LAYER2);
	glVertex3d(v1[0],v1[1], DRAW_LAYER2);
	glVertex3d(v2[0],v2[1], DRAW_LAYER2);
	glEnd();

	glPopMatrix();

	glColor4d(1.0,1.0,1.0,1.0);

	if (!debug) {
		vector<Character *> nearbyCharacters = parent->getCharacterManager()->getNearbyCharacters(parent->getPosition(),MAX_VIEW_FIELD_LENGTH+50.0);
		vector<Character *>::iterator it = nearbyCharacters.begin();
		while(it!=nearbyCharacters.end()){
			Character *c = (*it);
			it++;
			Character *player = CharacterManager::instance()->getCharacter("Player");
			if(c == player) continue;
			double size = c->getSize();
			CVector p = c->getPosition() - parent->getPosition();
			CVector v1 = CVector(p[0]-size,p[1]+size);
			CVector v2 = CVector(p[0]+size,p[1]+size);
			CVector v3 = CVector(p[0]-size,p[1]-size);
			CVector v4 = CVector(p[0]+size,p[1]-size);

			if(pointInView(v1)||pointInView(v2)||pointInView(v3)||pointInView(v4)){
				parent->getCharacterManager()->addDrawingCharacter(c);
			}
		}
	}
}


bool FieldOfViewComponent::pointInView(CVector p)
{
	CVector3 point = CVector3(p[0],p[1],0.0);

	CVector v1 = fov - CVector(-fov[1],fov[0])*M_PI/6;
	CVector v2 = fov - CVector(fov[1],-fov[0])*M_PI/6;
	CVector position = CVector(0,0);

	CVector3 a = CVector3(v1[0],v1[1],0.0);
	CVector3 b = CVector3(v2[0],v2[1],0.0);
	CVector3 c = CVector3(position[0],position[1],0.0);

	if(edgeSideTest(point,a,b,c) && edgeSideTest(point,b,a,c) && edgeSideTest(point,c,a,b))
		return true;
	else 
		return false;
}

bool FieldOfViewComponent::edgeSideTest(CVector3 p1,CVector3 p2, CVector3 a, CVector3 b)
{
	CVector3 cp1 = cp1.crossProduct(b-a,p1-a);
	CVector3 cp2 = cp1.crossProduct(b-a,p2-a);
	if(cp1*cp2 >= EPSILON)
		return true;
	else
		return false;
}

bool FieldOfViewComponent::isCharacterSeen(Character *c)
{
	vector<Character*>::iterator it = seenEnemies.begin();
	while(it!=seenEnemies.end()){
		Character *t = (*it);
		if(t==c)
			return true;

		it++;
	}
	return false;
}

