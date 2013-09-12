#pragma once
#include "core\Character.h"
#include "app\globaldefs.h"

class Component {

public:
	Component() { active = true; }
	virtual void setActive(bool a) { active = a; }
	virtual bool isActive() { return active;}

	virtual void attachToCharacter(Character *p) { if (!p) throw; parent = p; parent->addComponent(this); }
	virtual void update(double deltaTime) {};
	virtual void draw() {} 
	virtual Character *getCharacter() { return parent; }

	void setTag(Component_tag t) { tag = t; }
	Component_tag getTag() { return tag; }

protected:
	bool active;
	Character *parent;

	Component_tag tag;
};

template<class T> T* getComponent(Character *c) {
	
	T* comp = NULL;
	vector<Component*> components = c->attachedComponents();
	vector<Component*>::const_iterator it = components.cbegin();
	while(it != components.cend()) {

		comp = dynamic_cast<T*>(*it); 
		if (comp != NULL) {
			 break;
		}
		it++;
	}

	return comp;
}