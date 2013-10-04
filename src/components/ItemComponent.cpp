#include "ItemComponent.h"
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>   

ItemComponent::ItemComponent(int width,int height,Character *c)
{
	parent = NULL;
	attachToCharacter(c);
	active = true;
	this->width = width;
	this->height = height;
}


ItemComponent::~ItemComponent(void)
{
}


//Prüft ob der Gegegnstand aufgehoben wurde und spawnt ihn neu
void ItemComponent::update(double deltaTime){
	if(pickedUp){
		srand (time(NULL));
		int x = rand() %width;
		int y = rand() %height;
		setPosition(CVector(x,y));
		while((CharacterManager::instance()->getNearestCharacter(parent)->getPosition()-parent->getPosition()).getLength() < 150){
			x = rand()%width;
			y = rand()%height;
			setPosition(CVector(x,y));
		}
		pickedUp = false;
	}
}

void ItemComponent::draw(){

}