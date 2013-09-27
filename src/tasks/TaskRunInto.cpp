#include "TaskRunInto.h"
#include "app\globaldefs.h"
#include "core\Character.h"
#include "core\CharacterManager.h"
#include "components\MoveComponent.h"
#include "components\FieldOfViewComponent.h"
		
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