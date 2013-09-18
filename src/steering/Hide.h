#pragma once
#include "steering\Steering.h"
#include "mathutil\Vector.h"

class Hide : public PositionSteering
{
public:
	Hide(CVector pos);
	virtual ~Hide(void);

	virtual void apply(MoveComponent *);
	void retarget(CVector pos);
protected:
	CVector position;
};

