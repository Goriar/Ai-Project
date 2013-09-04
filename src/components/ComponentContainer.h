#pragma once
#include "components\ComponentContainer.h"
#include <vector>
using namespace std;

class Component;

class ComponentContainer  {

public:	
	ComponentContainer();
	~ComponentContainer();
	void update(double deltaTime);
	void draw();
	void addComponent(Component *c) { components.push_back(c); }
	const vector<Component*> &attachedComponents() { return components;}
	
protected:
	vector<Component*> components;

};