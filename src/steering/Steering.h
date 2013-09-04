#pragma once

class MoveComponent;

// Abstract interface for all position steering behaviours
//
class PositionSteering {
public:
	// apply the behaviour to the given character c
	virtual void apply(MoveComponent * c) = 0;

	// optional function helpful if the behaviour needs
	// to display something on the screen for debugging
	virtual void debugDraw(MoveComponent *) {}
};

// Abstract interface for all orientation steering behaviours
//
class AngularSteering {
public:
	// apply the behaviour to the given character c
	virtual void apply(MoveComponent *c) = 0;

	// optional function helpful if the behaviour needs
	// to display something on the screen for debugging
	virtual void debugDraw(MoveComponent *) {}
};