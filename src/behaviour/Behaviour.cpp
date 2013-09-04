#include "behaviour\Behaviour.h"
#include "app\globaldefs.h"
using namespace BehaviourTree;

Behaviour::Behaviour() {
	root = NULL;
	isRunning = false;
}

void Behaviour::start() {

	if (root != NULL) {
		root->activate();
		isRunning = true;
	}
}

Behaviour::~Behaviour(){
	if(root != NULL){
		delete root;
	}

}
void Behaviour::update(double deltaTime) {

	if (!isRunning) {
		start();
	}

	std::list<TaskNode *>::iterator it = activeTasks.begin();

	unsigned int numTasks = activeTasks.size();
	while(it != activeTasks.end()) {

		TaskNode *task = (*it++);
		task->run(deltaTime);
	}
}

void Behaviour::addChild(ChildNode *c) {
	root = c;
}

void Behaviour::childTerminated(ChildNode *c, bool result) {

	DEBUG_MESSAGE("Behaviour tree terminated " << ((result)? "successfully" : "without success!"));
	isRunning = false;
}