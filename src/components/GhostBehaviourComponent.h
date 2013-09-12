#pragma once

#include "app\globaldefs.h"
#include "components\Component.h"
#include "core\CharacterManager.h"
#include "components\MoveComponent.h"

class GhostBehaviourComponent : public Component
{
public:
	GhostBehaviourComponent(Character* ghost, MoveComponent* mc, CharacterManager *cm, Component_tag tag);
	virtual ~GhostBehaviourComponent(void);
	virtual void update(double deltaTime);
	void updateState();

	void setState( Ghost_state s) { if(state != FLEE) {state = s ; updateState();} } ;

protected: 
	Character* ghost;
	MoveComponent* mc;
	CharacterManager* cm;

	Ghost_state state;
	Ghost_state lastState;
};