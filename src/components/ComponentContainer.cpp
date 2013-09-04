#include "components\ComponentContainer.h"
#include "components\Component.h"

ComponentContainer::ComponentContainer() {

}

ComponentContainer::~ComponentContainer() {

	while(!components.empty()) {
		delete components.back();
		components.pop_back();
	}
}

void ComponentContainer::update(double deltaTime) {

	std::vector<Component *>::iterator it = components.begin();

	while(it != components.end()) {

		Component *comp = (*it);
		if (comp->isActive()) {
			comp->update(deltaTime);
		}
		it++;
	}

} 

void ComponentContainer::draw() {

	std::vector<Component *>::iterator it = components.begin();

	while(it != components.end()) {

		Component *comp = (*it);
		if (comp->isActive()) {
			comp->draw();
		}
		it++;
	}
}
