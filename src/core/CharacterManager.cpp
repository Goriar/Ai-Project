#include "core\CharacterManager.h"
#include "core\Character.h"

CharacterManager::CharacterManager() {

}

Character *CharacterManager::createCharacter(const string &name, unsigned int tag) {
	
	if (characters.find(name) != characters.end()) return NULL;

	Character *c = new Character(name,tag);
	characters[name] = c;

	return c;

}

void CharacterManager::deleteCharacter(const string &name) {
	map<string,Character*>::iterator it = characters.find(name);

	if (it != characters.end()) {
		characters.erase(it);
	}
}

void CharacterManager::draw() {

	map<string,Character*>::iterator it = characters.begin();
	while(it != characters.end()) {
		it->second->draw();
		it++;
	}
}

void CharacterManager::update(double timeDelta) {

	map<string,Character*>::iterator it = characters.begin();
	while(it != characters.end()) {
		it->second->update(timeDelta);
		it++;
	}
}
Character *CharacterManager::getNearestCharacter(CVector vec, unsigned int tag, double maxDistance) {
	
	Character *found = NULL;
	double nearest = maxDistance;
	
	map<string,Character*>::iterator it = characters.begin();
	
	while(it != characters.end()) {

		Character *c = it->second;
		it++;

		// check for tags
		if ((tag != 0) && (c->getTag() != tag)) continue;
		
		// check for maxDistance
		double dist = (c->getPosition() - vec).getLength();
		if (dist > maxDistance) continue;

		if (dist < nearest) {
			nearest = dist;
			found = c;
		}
	}

	return found;
}

vector<Character *> CharacterManager::getAllNearbyCharacters(CVector vec, unsigned int tag, double maxDistance) {

	nearbyCharacters.clear();
	map<string,Character*>::iterator it = characters.begin();
	while(it != characters.end()) {

		Character *c = it->second;
		it++;

		// check for tags
		if ((tag != 0) && (c->getTag() != tag)) continue;
		
		// check for maxDistance
		double dist = (c->getPosition() - vec).getLength();
		if (dist > maxDistance) continue;

		nearbyCharacters.push_back(c);
	}

	return nearbyCharacters;
}

Character *CharacterManager::getCharacter(string name) {
	
	map<string,Character*>::iterator it = characters.find(name);
	if (it != characters.end()) {
		return it->second;
	}

	return NULL;
}