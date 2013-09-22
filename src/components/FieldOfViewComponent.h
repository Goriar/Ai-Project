#pragma once
#include "mathutil\Vector.h"
#include "mathutil\Vector3.h"
#include "app\globaldefs.h"
#include "components\Component.h"
#include "core\CharacterManager.h"
#include <vector>


class FieldOfViewComponent : public Component
{
public:
	FieldOfViewComponent(CVector* mouse, Character *c = NULL);
	virtual ~FieldOfViewComponent(void);
	virtual void update(double deltaTime);
	virtual void draw();

	bool pointInView(CVector p);
	bool edgeSideTest(CVector3 p1,CVector3 p2, CVector3 a, CVector3 b);
	bool isCharacterSeen(Character* c);


protected: 
	CVector* mousePosition;
	CVector fov;
	std::vector<Character*> seenEnemies;

};

