#pragma once
#include "behaviour\BehaviourInterfaces.h"
#include <vector>

namespace BehaviourTree
{

	class Selector : public ParentNode, public ChildNode
	{
	public:
		Selector(ParentNode *p);
		virtual ~Selector(void);

		//ChildNode Interface
		virtual void activate();

		//ParentNode Interface
		virtual void addChild(ChildNode *c);
		virtual void childTerminated(ChildNode *c, bool result);
	protected:
		std::vector<ChildNode*> children;
		ParentNode* parent;
		int activeChild;
	};

}

