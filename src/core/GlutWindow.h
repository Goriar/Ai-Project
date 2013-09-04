#pragma once

#include "mathutil\Vector.h"
#include <windows.h>

class CArcBall;

class GlutWindow
{
public:
	GlutWindow(void);
	~GlutWindow(void);

	virtual void renderFrame();
	virtual void idle();
	virtual void resize(int width, int height);
	virtual void keyEvent(unsigned char key,int x,int y);
	virtual void mouseButtonEvent(int button, int state,int x,int y);
	virtual void mouseMoveEvent(int x,int y);
	virtual bool handleButtonEvent(int button, int state, int x, int y);
	virtual bool handleMoveEvent(int x, int y);

protected:
	int nWidth, nHeight;

	void initializeGL();

};



