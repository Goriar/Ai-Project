#pragma once
#include "behaviour\Behaviour.h"

class Character;
class MoveComponent;
class Seek;
class FieldOfViewComponent;

namespace BehaviourTree{
	class TaskRunInto : public TaskNode
	{
	public:
		TaskRunInto(Behaviour *b, ParentNode *p, Character *c);
		virtual ~TaskRunInto(void);

		virtual void activate();
		virtual void run(double deltaTime);
		virtual void deactivate();

	protected:
		Character  *character;
		BehaviourTree::ParentNode *parent;
		BehaviourTree::Behaviour  *behaviour;
		MoveComponent *moveComp;
		Seek *seekBehaviour;
		FieldOfViewComponent *fov;
		Character *player;
	};
}