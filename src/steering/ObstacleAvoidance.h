#pragma once

#include "steering\Steering.h"

class Character;


class ObstacleAvoidance : public PositionSteering {
	
public:
	ObstacleAvoidance(Character *target);
	virtual void apply(MoveComponent *);
	virtual void debugDraw(MoveComponent *);
	void retarget(Character *c) { target = c; }
	static void avoideObstacles(MoveComponent *, bool avoid_player);

protected:
	double box_length;
	Character *target;
};
