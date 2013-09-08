#pragma once
#include "core/GlutWindow.h"
#include "behaviour/Behaviour.h"
#include "app/globaldefs.h"
#include "components\PlayerMoveComponent.h"
#include "components\FieldOfViewComponent.h"
#include <vector>

class Character;

class AIWindow : public GlutWindow
{
public:
	AIWindow();
	virtual ~AIWindow(void);

	virtual void renderFrame();
	virtual void keyEvent(unsigned char key,int x,int y);
	virtual void keyUpEvent(unsigned char key,int x,int y);

	virtual bool handleButtonEvent(int button, int state, int x, int y);
	virtual bool handleMoveEvent(int x, int y);


protected:
	bool bDragging;
	Character *dragCharacter;
	Character *player;
	Character *enemy;
	CVector *fov;
	bool* keyStates;
	BehaviourTree::Behaviour *behaviour;

	void createBehaviour();
	double getTimeDelta();

	void createPlayer();
	void createEnemy();
};
