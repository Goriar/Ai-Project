#pragma once
#include "behaviour\Behaviour.h"

class Character;
class MoveComponent;
class Seek;
class FieldOfViewComponent;

namespace BehaviourTree{
	class TaskWaitForAction : public TaskNode
	{
	public:
		TaskWaitForAction(Behaviour *b, ParentNode *p, Character *c);
		virtual ~TaskWaitForAction(void);

		virtual void activate();
		virtual void run(double deltaTime);
		virtual void deactivate();

	protected:
		Character  *character;
		BehaviourTree::ParentNode *parent;
		BehaviourTree::Behaviour  *behaviour;
		MoveComponent *moveComp;
		FieldOfViewComponent *fov;
		Character* player;
	};
}