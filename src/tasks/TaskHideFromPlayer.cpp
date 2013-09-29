#include "TaskHideFromPlayer.h"
#include "app\globaldefs.h"
#include "core\Character.h"
#include "core\CharacterManager.h"
#include "components\MoveComponent.h"
#include "components\FieldOfHideComponent.h"
#include "steering\Hide.h"
#include "components\PlayerMoveComponent.h"


using namespace BehaviourTree;

TaskHideFromPlayer::TaskHideFromPlayer(Behaviour *b, ParentNode *p, Character *c)
{
	behaviour = b;
	parent = p;
	character = c;
	parent->addChild(this);

	moveComp = getComponent<MoveComponent>(character);
	hideBehaviour = new Hide(CVector());
	foh = NULL;
}


TaskHideFromPlayer::~TaskHideFromPlayer(void)
{
}

void TaskHideFromPlayer::activate()
{
	Character* hidingSpot = CharacterManager::instance()->getNearestCharacter(character->getPosition(),OBSTACLE_TAG);
	foh = getComponent<FieldOfHideComponent>(hidingSpot);
	hideBehaviour->retarget(foh->getCenterPosition());
	moveComp->setPositionSteering(hideBehaviour);
	behaviour->activateTask(this);
}

void TaskHideFromPlayer::run(double deltaTime)
{
	Character *player = CharacterManager::instance()->getCharacter("Player");
	if((character->getPosition() - player->getPosition()).getLength() <= GHOST_PLAYER_DIST)
	{
		// Player dies
		PlayerMoveComponent *movComp = getComponent<PlayerMoveComponent>(player);
		movComp->loseHealth(1);
	}

	hideBehaviour->retarget(foh->getCenterPosition());
	if((character->getPosition()-foh->getCenterPosition()).getLength() < 20.0){
		deactivate();
		parent->childTerminated(this,true);
	}

	if((character->getPosition() - player->getPosition()).getLength() >= MAX_VIEW_FIELD_LENGTH)
	{
		deactivate();
		parent->childTerminated(this,true);
		return;
	}
}

void TaskHideFromPlayer::deactivate()
{
	foh = NULL;
	moveComp->setPositionSteering(NULL);
	behaviour->deactivateTask(this);
}