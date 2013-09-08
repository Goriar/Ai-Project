#pragma once
#include "mathutil\Vector.h"
#include "mathutil\Vector3.h"
#include "core\Character.h"
#include "components\Component.h"

#define MAX_VIEW_FIELD_LENGTH (300.0)

class PlayerMoveComponent : public Component
{

public:
	PlayerMoveComponent(bool *keys, Character *c = NULL);
	virtual ~PlayerMoveComponent(void);
	virtual void update(double deltaTime);
	virtual void draw();
	
	inline const CVector &getPosition()          const { if (!parent) throw; return parent->getPosition();}
	inline const CVector &getVelocity()          const { return velocity;    }
	inline double         getRotation()          const { if (!parent) throw; return parent->getRotation();}
	inline double         getAngularVelocity()   const { return angularVelo; }
	
	
	void setPosition(const CVector &vec);
	void setRotation(double v);   
	inline void setMaxVelocity(double d)        { maxVelocity = d;       }	
	inline void setMaxAngularVelocity(double d) { maxAngularVelocity = d;}
	
	inline double getMaxVelocity()        { return maxVelocity;        }	
	inline double getMaxAngularVelocity() { return maxAngularVelocity; }
	inline double getMaxAccel()           { return maxAccel;           }	
	inline double getMaxAngularAccel()    { return maxAngularAccel;    }

	void setVelocity(const CVector &vec);
	void setAccel(const CVector &vec);     
	void setAngularVelocity(double v);  
	void setAngularAccel(double v);
	void setMousePosition(CVector mouse);
	bool pointInView(CVector p);
	bool edgeSideTest(CVector3 p1,CVector3 p2, CVector3 a, CVector3 b);
	void determineDirection();

protected:
	CVector mousePosition;
	CVector velocity;
	CVector accel;
	CVector fov;
	bool* keyStates;
	double angularVelo;
	double angularAccel;
	
	double maxVelocity;
	double maxAngularVelocity;
	double maxAccel;
	double maxAngularAccel;
};
