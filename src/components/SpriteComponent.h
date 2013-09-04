#pragma once
#include "components\Component.h"
#include "mathutil\Vector.h"
#include "steering\Steering.h"

class Sprite;

class SpriteComponent : public Component {

public:
	SpriteComponent(Character *c, Sprite *sprite, double size = 64.0);
    virtual void draw();

protected:
	double size;
	Sprite *sprite;

};