#include "TaskRunInto.h"
#include "app\globaldefs.h"
#include "core\Character.h"
#include "core\CharacterManager.h"
#include "components\MoveComponent.h"
#include "components\FieldOfViewComponent.h"
#include "components\PlayerMoveComponent.h"
		
#include "steering\Seek.h"


using namespace BehaviourTree;

TaskRunInto::TaskRunInto(Behaviour *b, ParentNode *p, Character *c)
{
	behaviour = b;
	parent = p;
	character = c;
	parent->addChild(this);
	fov = NULL;
	player = NULL;

	moveComp = getComponent<MoveComponent>(character);
	seekBehaviour = new Seek(NULL);
}


TaskRunInto::~TaskRunInto(void)
{
}

void TaskRunInto::activate()
{
	player = CharacterManager::instance()->getCharacter("Player");
	fov = getComponent<FieldOfViewComponent>(player);
	seekBehaviour->retarget(player);
	moveComp->setPositionSteering(seekBehaviour);
	behaviour->activateTask(this);
}

void TaskRunInto::run(double deltaTime)
{
	Character *player = CharacterManager::instance()->getCharacter("Player");
	if((character->getPosition() - player->getPosition()).getLength() <= GHOST_PLAYER_DIST)
	{
		// Player dies
		PlayerMoveComponent *movComp = getComponent<PlayerMoveComponent>(player);
		movComp->loseHealth(5);
	}

	if( !fov->isCharacterSeen(character) )
	{
		deactivate();
		parent->childTerminated(this,true);
		return;
	}
}

void TaskRunInto::deactivate()
{
	moveComp->setAccel(CVector(0,0));
	moveComp->setVelocity(CVector(0,0));
	moveComp->setPositionSteering(NULL);
	behaviour->deactivateTask(this);
}