#include "Selector.h"

using namespace BehaviourTree;

Selector::Selector(ParentNode *p)
{
	parent = p;
	activeChild = -1;
	parent->addChild(this);
}


Selector::~Selector(void)
{
	while(!children.empty())
	{
		delete children.back();
		children.pop_back();
	}
}

void Selector::activate()
{
	if(children.size() > 0)
	{
		activeChild = 0;
		children[0]->activate();
	}
}

void Selector::addChild(ChildNode *c)
{
	children.push_back(c);
}

void Selector::childTerminated(ChildNode *c, bool result)
{
	if(result)
	{
		parent->childTerminated(this,true);
	} else {
		activeChild++;
		if(activeChild == children.size())
		{
			//Selector gescheitert, keine weiteren Optionen
			parent->childTerminated(this,false);
		} else {
			children[activeChild]->activate();
		}
	}
}
