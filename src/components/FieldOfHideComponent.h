#pragma once
#include "mathutil\Vector.h"
#include "mathutil\Vector3.h"
#include "app\globaldefs.h"
#include "components\Component.h"
#include "core\CharacterManager.h"
#define MAX_HIDE_FIELD_LENGTH (100)
class FieldOfHideComponent :
	public Component
{
public:
	FieldOfHideComponent(Character *player, CharacterManager *cm, Character *c);
	virtual ~FieldOfHideComponent(void);
	virtual void update(double deltaTime);
	virtual void draw();

	CVector getCenterPosition();
protected: 
	CVector foh;
	Character *player;

	CharacterManager *characterManager;
};