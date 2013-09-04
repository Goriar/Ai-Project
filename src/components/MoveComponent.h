#pragma once
#include "components\Component.h"
#include "mathutil\Vector.h"
#include "steering\Steering.h"
#include "core\Character.h"

class MoveComponent : public Component {

public:
	MoveComponent(Character *c = NULL);

	virtual void attachToCharacter(Character *p);
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

	inline void setPositionSteering(PositionSteering *p) { posSteering = p; }
	inline void setAngularSteering(AngularSteering *a)   { angularSteering = a; }

protected:
	Character *parent;
	CVector velocity;
	CVector accel;

	double angularVelo;
	double angularAccel;

	PositionSteering *posSteering;
	AngularSteering *angularSteering;
	
	double maxVelocity;
	double maxAngularVelocity;
	double maxAccel;
	double maxAngularAccel;

};