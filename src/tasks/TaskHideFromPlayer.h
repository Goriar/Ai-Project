#pragma once
#include "behaviour\Behaviour.h"

class Character;
class MoveComponent;
class FieldOfHideComponent;
class Hide;
class ObstacleAvoidance;

namespace BehaviourTree{
	class TaskHideFromPlayer : public TaskNode
	{
	public:
		TaskHideFromPlayer(Behaviour *b, ParentNode *p, Character *c);
		virtual ~TaskHideFromPlayer(void);

		virtual void activate();
		virtual void run(double deltaTime);
		virtual void deactivate();

	protected:
		Character  *character;
		BehaviourTree::ParentNode *parent;
		BehaviourTree::Behaviour  *behaviour;
		MoveComponent *moveComp;
		Hide *hideBehaviour;

		FieldOfHideComponent *foh;
	};
}

