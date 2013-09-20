#pragma once
#include "behaviour\Behaviour.h"

class Character;
class MoveComponent;
class Seek;
class FieldOfViewComponent;
class ObstacleAvoidance;

namespace BehaviourTree{
	class TaskPursuePlayer : public TaskNode
	{
	public:
		TaskPursuePlayer(Behaviour *b, ParentNode *p, Character *c);
		~TaskPursuePlayer(void);

		virtual void activate();
		virtual void run(double deltaTime);
		virtual void deactivate();

	protected:
		Character  *character;
		BehaviourTree::ParentNode *parent;
		BehaviourTree::Behaviour  *behaviour;

		MoveComponent *moveComp;
		Seek * seekBehaviour;
		Character *player;
		FieldOfViewComponent *fov;
	};
}

