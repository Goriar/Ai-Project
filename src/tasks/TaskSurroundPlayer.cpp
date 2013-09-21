#include "TaskSurroundPlayer.h"
#include "app\globaldefs.h"
#include "core\Character.h"
#include "core\CharacterManager.h"
#include "components\MoveComponent.h"
#include "steering\Hide.h"
#include "components\FieldOfViewComponent.h"

using namespace BehaviourTree;

TaskSurroundPlayer::TaskSurroundPlayer(Behaviour *b, ParentNode *p, Character *c)
{
	behaviour = b;
	parent = p;
	character = c;
	parent->addChild(this);
	targetPosition = CVector();
	moveComp = getComponent<MoveComponent>(character);
	player = CharacterManager::instance()->getNearestCharacter(character->getPosition(),PLAYER_TAG);
	hideBehaviour = new Hide(CVector());
	fov = getComponent<FieldOfViewComponent>(player);
}


TaskSurroundPlayer::~TaskSurroundPlayer(void)
{
}

void TaskSurroundPlayer::activate()
{
	calculateTargetPosition();
	hideBehaviour->retarget(targetPosition);
	moveComp->setPositionSteering(hideBehaviour);
	behaviour->activateTask(this);
}
void TaskSurroundPlayer::run(double deltaTime)
{
	calculateTargetPosition();
	hideBehaviour->retarget(targetPosition);
	if((character->getPosition()-player->getPosition()).getLength() <= 10.0)
	{
		deactivate();
		parent->childTerminated(this,true);
	}

	if(fov->isCharacterSeen(character)){
		deactivate();
		parent->childTerminated(this,false);
		return;
	}
}

void TaskSurroundPlayer::deactivate()
{
	moveComp->setPositionSteering(NULL);
	behaviour->deactivateTask(this);
}

void TaskSurroundPlayer::calculateTargetPosition()
{
	CVector closestAlly = CharacterManager::instance()->getNearestCharacter(character->getPosition(),GHOST_TAG)->getPosition();
	
	CVector d = player->getPosition() - closestAlly;
	CVector h = closestAlly - d;
	double a = d * d;
	double b = 2*(d * h);
	double c = h*h - SURROUND_RADIUS*SURROUND_RADIUS;

	double delta1 = (-b + sqrt(b*b - 4*a*c))/2*a;
	double delta2 = (-b - sqrt(b*b - 4*a*c))/2*a;

	closestAlly = (closestAlly - (closestAlly + delta1*d)).getLength() < (closestAlly - (closestAlly + delta2*d)).getLength() ? closestAlly + delta1*d : closestAlly + delta2*d;

	targetPosition = closestAlly - player->getPosition();
	targetPosition[0] = SURROUND_RADIUS * sin(M_PI/4);
	targetPosition[1] = SURROUND_RADIUS * cos(M_PI/4);
	targetPosition += player->getPosition();
}

