#include "Sequence.h"

using namespace BehaviourTree;

Sequence::Sequence(ParentNode* p)
{
	parent = p;
	activeChild = -1;
	parent->addChild(this);
}


Sequence::~Sequence(void)
{
	while(!children.empty())
	{
		delete children.back();
		children.pop_back();
	}
}


void Sequence::activate()
{
	if(children.size() > 0)
	{
		activeChild = 0;
		children[0]->activate();
	}
}

void Sequence::addChild(ChildNode *c)
{
	children.push_back(c);
}

void Sequence::childTerminated(ChildNode *c, bool result)
{
	if(!result)
	{
		//Sequenz fehlgeschlagen
		parent->childTerminated(this,false);
	} else {
		//Teilaufgabe gelungen
		activeChild++;
		if(activeChild == children.size())
		{
			//Sequence erfolgreich
			parent->childTerminated(this,true);
		} else {
			//Teilaufgabe gelungen
			children[activeChild]->activate();
		}
	}
}