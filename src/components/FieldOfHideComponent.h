#pragma once
#include "mathutil\Vector.h"
#include "mathutil\Vector3.h"
#include "app\globaldefs.h"
#include "components\Component.h"
#include "core\CharacterManager.h"
#define MAX_HIDE_FIELD_LENGTH (150)
class FieldOfHideComponent :
	public Component
{
public:
	FieldOfHideComponent(Character *player, CharacterManager *cm, Character *c);
	virtual ~FieldOfHideComponent(void);
	virtual void update(double deltaTime);
	virtual void draw();
	bool ghostInPolygon(CVector ve1, CVector ve2, CVector ve3, CVector ve4);
	CVector getCenterPosition();
protected: 
	CVector foh;
	Character *player;

	CharacterManager *characterManager;
	bool pointInPolygon(CVector v,CVector s, CVector e);
	//Ecken des Field of Hide
	CVector v1, v2, v3, v4;
};