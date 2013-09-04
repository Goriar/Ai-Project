#pragma once 
#include <list>
#include "behaviour\BehaviourInterfaces.h"

namespace BehaviourTree {

	class Behaviour : public ParentNode {

	public:
		Behaviour();
		~Behaviour();
		virtual void start();
		virtual void update(double deltaTime);
		virtual void addChild(ChildNode *c);
		virtual void childTerminated(ChildNode *c, bool result);

		inline void activateTask(TaskNode *t) { activeTasks.push_back(t); } 
		inline void deactivateTask(TaskNode *t) { activeTasks.remove(t); } 
	protected:
		bool isRunning;
		ChildNode* root;
		std::list<TaskNode *> activeTasks;

	};

}