#include "TaskPursuePlayer.h"
#include "core\Character.h"
#include "core\CharacterManager.h"
#include "components\MoveComponent.h"
#include "steering\Seek.h"
#include "steering\ObstacleAvoidance.h"
#include "components\FieldOfViewComponent.h"
#include "components\PlayerMoveComponent.h"

using namespace BehaviourTree;

TaskPursuePlayer::TaskPursuePlayer(Behaviour *b, ParentNode *p, Character *c)
{
	character = c;
	parent = p;
	parent->addChild(this);
	behaviour = b;

	moveComp = getComponent<MoveComponent>(character);
	seekBehaviour = new Seek(NULL);
	player = CharacterManager::instance()->getNearestCharacter(character->getPosition(),PLAYER_TAG);
	fov = getComponent<FieldOfViewComponent>(player);
}


TaskPursuePlayer::~TaskPursuePlayer(void)
{

}

void TaskPursuePlayer::activate()
{
	seekBehaviour->retarget(player);
	moveComp->setPositionSteering(seekBehaviour);
	behaviour->activateTask(this);
}

void TaskPursuePlayer::run(double deltaTime)
{
	//Pr�ft ob der Spieler nah genug am Gegner ist um Lebenspunkte zu verlieren
	if((character->getPosition() - player->getPosition()).getLength() <= GHOST_PLAYER_DIST)
	{
		PlayerMoveComponent *movComp = getComponent<PlayerMoveComponent>(player);
		movComp->loseHealth(1);
	}

	//Wenn der Gegner weit vom Spieler entfernt ist wechselt er ins Surround Behaviour
	if((character->getPosition() - player->getPosition()).getLength() >= SURROUND_RADIUS)
	{
		deactivate();
		parent->childTerminated(this,true);
		return;
	}

	//Wenn er gesehen wird versteckt er sich
	if(fov->isCharacterSeen(character)){
		deactivate();
		parent->childTerminated(this,false);
		return;
	}
	
}

void TaskPursuePlayer::deactivate()
{
	behaviour->deactivateTask(this);
	moveComp->setPositionSteering(NULL);
}
