#pragma once
#include "behaviour\Behaviour.h"
#include "mathutil\Vector.h"
#include "components\FieldOfViewComponent.h"

class Character;
class MoveComponent;
class Hide;


namespace BehaviourTree{
	class TaskSurroundPlayer : public TaskNode
	{
	public:
		TaskSurroundPlayer(Behaviour *b, ParentNode *p, Character *c);
		virtual ~TaskSurroundPlayer(void);

		virtual void activate();
		virtual void run(double deltaTime);
		virtual void deactivate();
		void calculateTargetPosition();
	protected:
		Character  *character;
		BehaviourTree::ParentNode *parent;
		BehaviourTree::Behaviour  *behaviour;

		Character *player;
		MoveComponent *moveComp;
		CVector targetPosition;
		Hide *hideBehaviour;
		FieldOfViewComponent *fov;
	};
}
