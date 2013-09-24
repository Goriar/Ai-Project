#include "components\SpriteComponent.h"
#include "core\Sprite.h"
#include "app\globaldefs.h"
#include <windows.h>
#include <GL\GL.h>
#include <stdio.h>

SpriteComponent::SpriteComponent(Character *c, Sprite *s) {

	size = c->getSize();
	sprite = s;
	parent = NULL;
	if (c != NULL) {
		attachToCharacter(c);
	}
	active = true;
}

void SpriteComponent::draw() {

	if (parent == NULL) return;

	CVector position = parent->getPosition();
	glMatrixMode(GL_MODELVIEW_MATRIX);
	glPushMatrix();
	glTranslated(position[0],position[1],0.0);
	
	sprite->bind();
	
	glBegin(GL_QUADS);
	glTexCoord2d(0.0, 1.0); glVertex2d(-size, -size);
	glTexCoord2d(0.0, 0.0); glVertex2d(-size,  size);
	glTexCoord2d(1.0, 0.0); glVertex2d( size,  size);
	glTexCoord2d(1.0, 1.0); glVertex2d( size, -size);
	glEnd();

	glDisable(GL_TEXTURE_2D);

	glPopMatrix();
	glColor4d(1.0,1.0,1.0,1.0);

}