#pragma once

#include "components\ComponentContainer.h"
#include "mathutil/Vector.h"
#include "core\CharacterManager.h"
#include <vector>
using namespace std;

class Component;

class Character : public ComponentContainer {
	
public:
	
	inline const CVector &getPosition()          const { return position;    }
	inline double         getRotation()          const { return rotation;    }
	const string         &getName()              const { return name;        }
	void setPosition(const CVector &vec);
	void setRotation(double v);   
	void setSize(double s);
	void setCharacterManager(CharacterManager *cm);
	inline CharacterManager *getCharacterManager() const { return characterManager;}
	inline double getSize() const { return size; }


	void setTag(unsigned int t) { tag = t; }
	unsigned int getTag() { return tag; }
	
private:
	// Constructor is private, use CharacterManager::createCharacter to create characters
	Character(const string &name, unsigned int tag = 0, double size = 64.0);
	// Destructor is private, use CharacterManager::deleteCharacter to destroy characters
	~Character();

protected:
	CVector position;
	double rotation;
	double size;
	CharacterManager *characterManager;

	unsigned int tag;
	string name;

	friend class CharacterManager;
};
