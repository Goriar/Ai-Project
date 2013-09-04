#include "core/Character.h"
#include "core/CharacterManager.h"
#include <math.h>
#include <assert.h>
#include <stdio.h>
#include <windows.h>
#include <GL/gl.h>
#include "app/globaldefs.h"
#include "steering/Steering.h"
#include "components\Component.h"

Character::Character(const string &n, unsigned int t) {

	name = n;
	position.set(0.0,0.0);
	rotation = 0.0;
	tag = t;
}

Character::~Character() {

}

void Character::setPosition(const CVector &vec)  {position = vec;  }
void Character::setRotation(double v)            {rotation = v; }	
