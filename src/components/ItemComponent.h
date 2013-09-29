#pragma once
#include "components\Component.h"

class ItemComponent : public Component
{
public:
	ItemComponent(int width,int height,Character *c = NULL);
	virtual ~ItemComponent(void);
	virtual void update(double deltaTime);
	virtual void draw();

	inline const CVector &getPosition()          const { if (!parent) throw; return parent->getPosition();}
	inline void setPosition(CVector pos) { parent->setPosition(pos);}
	inline void pickUp(){ pickedUp = true;}

protected:
	bool pickedUp;
	int width;
	int height;
};

