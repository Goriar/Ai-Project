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
	if((targetPosition-character->getPosition()).getLength() <= 80.0 || targetPosition.isNil()||(player->getPosition()-character->getPosition()).getLength() <= MAX_VIEW_FIELD_LENGTH )
	{
		deactivate();
		parent->childTerminated(this,true);
		return;
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
	Character *ally = CharacterManager::instance()->getNearestCharacter(character,GHOST_TAG);
	
	if(ally==NULL) {
		targetPosition = CVector();
		return;
	}
	CVector closestAlly = ally->getPosition();
	CVector d = player->getPosition() - closestAlly;
	d.normalize();
	CVector h = closestAlly - player->getPosition();
	double a = d * d;
	double b = 2*(d * h);
	double c = h*h - SURROUND_RADIUS*SURROUND_RADIUS;

	double delta1 = (-b + sqrt(b*b - 4*a*c))/2*a;
	double delta2 = (-b - sqrt(b*b - 4*a*c))/2*a;

	CVector t = (closestAlly - (closestAlly + delta1*d)).getLength() < (closestAlly - (closestAlly + delta2*d)).getLength() ? closestAlly + delta1*d : closestAlly + delta2*d;

	//cout << closestAlly[0] << " " << closestAlly[1] << " " << CharacterManager::instance()->getNearestCharacter(character->getPosition(),GHOST_TAG,80.0)->getName() << endl;
	MoveComponent *mov = getComponent<MoveComponent>(ally);
	CVector velo = mov->getVelocity();
	velo.normalize();

	targetPosition = t - player->getPosition();
	if((velo-character->getPosition()).getLength()>=((velo+CVector(-velo[1],velo[0]))-character->getPosition()).getLength()){
		targetPosition[0] += (SURROUND_RADIUS * cos(90.0));
		targetPosition[1] += (SURROUND_RADIUS * sin(90.0));
	} else {
		targetPosition[0] -= (SURROUND_RADIUS * cos(90.0));
		targetPosition[1] -= (SURROUND_RADIUS * sin(90.0));
	}
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glTranslated(player->getPosition()[0],player->getPosition()[1],0.0);

	glColor3f(1.0,0.0,0.0);
	glDisable(GL_TEXTURE_2D);
	glBegin(GL_LINES);
	glVertex2d(0.0,0.0);
	glVertex2d(targetPosition[0],targetPosition[1]);
	glEnd();
	glPopMatrix();
	

	targetPosition += player->getPosition();
}

