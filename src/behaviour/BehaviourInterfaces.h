#pragma once

namespace BehaviourTree {

	class ChildNode {
	public:
		virtual void activate() = 0;
	};

	class ParentNode {
	public:
		virtual void addChild(ChildNode *c) = 0;
		virtual void childTerminated(ChildNode *c, bool result) = 0;
	};

	class TaskNode : public ChildNode {
	public:
		virtual void run(double deltaTime) = 0;
	};

}