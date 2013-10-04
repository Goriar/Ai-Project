#include "TaskWaitForAction.h"
#include "app\globaldefs.h"
#include "core\Character.h"
#include "core\CharacterManager.h"
#include "components\MoveComponent.h"
#include "components\FieldOfViewComponent.h"
#include "components\PlayerMoveComponent.h"


using namespace BehaviourTree;

// attention circle or point
TaskWaitForAction::TaskWaitForAction(Behaviour *b, ParentNode *p, Character *c)
{
	behaviour = b;
	parent = p;
	character = c;
	parent->addChild(this);
	player = NULL;

	moveComp = getComponent<MoveComponent>(character);
}


TaskWaitForAction::~TaskWaitForAction(void)
{
}

void TaskWaitForAction::activate()
{
	player = CharacterManager::instance()->getCharacter("Player");
	fov = getComponent<FieldOfViewComponent>(player);
	moveComp->setAccel(CVector(0,0));
	behaviour->activateTask(this);
}

void TaskWaitForAction::run(double deltaTime)
{
	// Normal Ghosts, with a circle
	//if( (character->getPosition() - player->getPosition()).getLength() < GHOST_ATTENTION_RADIUS )
	//{
	//	deactivate();
	//	parent->childTerminated(this,true);
	//	return;
	//}

	// Other Ghost reacts if its in fov

	//Wenn er gesehen wird, geht er auf den Character los
	if( fov->isCharacterSeen(character) )
	{
		deactivate();
		parent->childTerminated(this,true);
		return;
	}

	//Prüft ob der Spieler nah genug dran ist um Leben zu verlieren
	Character *player = CharacterManager::instance()->getCharacter("Player");
	if((character->getPosition() - player->getPosition()).getLength() <= GHOST_PLAYER_DIST)
	{
		// Player dies
		PlayerMoveComponent *movComp = getComponent<PlayerMoveComponent>(player);
		movComp->loseHealth(5);
	}
}

void TaskWaitForAction::deactivate()
{
	moveComp->setPositionSteering(NULL);
	behaviour->deactivateTask(this);
}