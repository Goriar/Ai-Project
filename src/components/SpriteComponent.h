#pragma once
#include "components\Component.h"
#include "mathutil\Vector.h"
#include "steering\Steering.h"

class Sprite;

class SpriteComponent : public Component {

public:
	SpriteComponent(Character *c, Sprite *sprite);
    virtual void draw();

protected:
	double size;
	Sprite *sprite;

};