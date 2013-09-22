#pragma once
#include "core\Singleton.h"
#include "mathutil\Vector.h"
#include "app\globaldefs.h"
#include <map>
#include <string>
#include <vector>
using namespace std;

class Character;

class CharacterManager : public Singleton<CharacterManager> {
	
public:
	CharacterManager();
	Character *createCharacter(const string &name, unsigned int tag = 0, double size = 64.0);
	void deleteCharacter(const string &name);

	Character *getNearestCharacter(CVector vec, unsigned int tag = 0, double maxDistance = DBL_MAX); 
	Character *getNearestCharacter(Character *searcher, unsigned int tag = 0, double maxDistance = DBL_MAX); 
	vector<Character *> getAllNearbyCharacters(CVector vec, unsigned int tag = 0, double maxDistance = DBL_MAX);
	vector<Character *> getNearbyCharacters(CVector vec, double maxDistance = DBL_MAX);
	Character *getCharacter(string name);
	void draw();
	void update(double deltaTime);

private:
	void addCharacter(const string &name, Character *s);

private:
	map<string, Character *> characters;
	vector<Character *> nearbyCharacters;
 
};