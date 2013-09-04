#pragma once

#include "components\ComponentContainer.h"
#include "mathutil/Vector.h"
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

	void setTag(unsigned int t) { tag = t; }
	unsigned int getTag() { return tag; }
	
private:
	// Constructor is private, use CharacterManager::createCharacter to create characters
	Character(const string &name, unsigned int tag = 0);
	// Destructor is private, use CharacterManager::deleteCharacter to destroy characters
	~Character();

protected:
	CVector position;
	double rotation;

	unsigned int tag;
	string name;

	friend class CharacterManager;
};
