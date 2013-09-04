#pragma once
#include "components\Component.h"
#include "mathutil\Vector.h"
#include "steering\Steering.h"

class Sprite {

public:
	Sprite(const char *filename);
    virtual void bind();

protected:
	unsigned int texId;
protected:
	void loadTexture(const char* filename);
	double size;

};