#include "GhostBehaviourComponent.h"

#include "steering\Wander.h"
#include "steering\Flee.h"
#include "steering\Seek.h"
#include "steering\Idle.h"

GhostBehaviourComponent::GhostBehaviourComponent(Character* c, MoveComponent* m, CharacterManager *charam)
{
	ghost = c;
	mc = m;
	cm = charam;
	attachToCharacter(c);

	state = SEEK;
	lastState = state;
	updateState();
}

GhostBehaviourComponent::~GhostBehaviourComponent()
{}

void GhostBehaviourComponent::update(double deltaTime)
{
	CVector currentPosition = mc->getPosition();
	CVector currentVelocity = mc->getVelocity();
	
	CVector desiredPosition = cm->getCharacter("Player")->getPosition();
	CVector desiredVelocity = desiredPosition-currentPosition;

	if(desiredVelocity.getLength() <  GHOST_PLAYER_DIST && lastState != IDLE)
	{
		state = IDLE;
		lastState = state;
		updateState();
	}
	else if(desiredVelocity.getLength() >  GHOST_PLAYER_DIST && lastState == IDLE)
	{
		state = SEEK;
		lastState = state;
		updateState();
	}


}

void GhostBehaviourComponent::updateState()
{
	switch(state){
	case IDLE:
		{
			mc->setVelocity(CVector(0.0f,0.0f));
			mc->setAccel(CVector(0.0f,0.0f));

			mc->setPositionSteering(new Idle(ghost->getPosition()));
			return;
		}
	case SEEK:
		{
			mc->setPositionSteering(new Seek(cm->getCharacter("Player")));
			return;
		}

	case FLEE:
		{
			return;
		}

	}
}