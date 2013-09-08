#include "app\AIWindow.h"
#include "core\Character.h"
#include "core\Sprite.h"
#include "core\CharacterManager.h"
#include <math.h>
#include <GL/glut.h>
#include <stdio.h>
#include <assert.h>

#include "components\MoveComponent.h"
#include "components\SpriteComponent.h"

#include "behaviour\Behaviour.h"
#include "behaviour\Sequence.h"
#include "behaviour\Selector.h"

using namespace BehaviourTree;

#include <sys\timeb.h>	
#include <time.h>



void AIWindow::createBehaviour() {

	behaviour = new Behaviour();
	Selector *rechargeSelector = new Selector(behaviour);
	Sequence *cleanupSequence = new Sequence(rechargeSelector);
}


AIWindow::AIWindow()
{
	dragCharacter = NULL;
	bDragging = false;
	keyStates = new bool[256];
	memset(keyStates,0,256);
	fov = new CVector();

	createPlayer();
	createBehaviour();

	glClearColor(1.0, 1.0, 1.0, 1.0);
	srand(time(0));
}

AIWindow::~AIWindow(void)
{
	delete behaviour;
}

void AIWindow::createPlayer(){
	CharacterManager *cm = CharacterManager::instance();
	player = cm->createCharacter("Player",PLAYER_TAG);
	player->setPosition(CVector(nWidth/2,nHeight/2));

	Sprite *sprite = new Sprite("..\\input\\robot_7.raw");
	SpriteComponent *sc = new SpriteComponent(player,sprite);

	PlayerMoveComponent *pMovComp = new PlayerMoveComponent(keyStates,player);
	FieldOfViewComponent *fovComponent = new FieldOfViewComponent(fov,cm,player);

	ghost = cm->createCharacter("Ghost",GHOST_TAG);
	ghost->setPosition(CVector(nWidth/2,nHeight/2));

	Sprite *sprite2 = new Sprite("..\\input\\robot_1.raw");
	SpriteComponent *sc2 = new SpriteComponent(ghost,sprite2);

	
}

void AIWindow::renderFrame() {

	static bool first = true;
	if (first) {
		getTimeDelta();
		first = false;
	}

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glViewport(0,0,nWidth,nHeight);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, nWidth, 0.0, nHeight, 0.0, 1.0);
	
	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	double timeDelta = getTimeDelta();

	CharacterManager *cm = CharacterManager::instance();
	
	cm->update(timeDelta);
	behaviour->update(timeDelta);

	cm->draw();

	glutSwapBuffers();

}


bool AIWindow::handleButtonEvent(int button, int state, int x, int y) {
	bDragging = (state == GLUT_DOWN);
	return false;
}

bool AIWindow::handleMoveEvent(int x, int y) {
	if ((bDragging) && (dragCharacter != NULL)) {
		dragCharacter->setPosition(CVector(x,nHeight-y));
	}
	fov->set(x,nHeight-y);
	return false;
}
void AIWindow::keyEvent(unsigned char key,int x,int y){

	keyStates[key] = true;

}

void AIWindow::keyUpEvent(unsigned char key,int x,int y){

	keyStates[key] = false;
}




double AIWindow::getTimeDelta() {

	__time64_t ltime;
	struct __timeb64 tstruct;

	static bool bFirstTime = true;
	static long nStartMilliSeconds;
	static long nMilliSeconds = 0;
	static long nStartCount   = 0;

	if (bFirstTime) {
		_time64( &ltime );
		nStartMilliSeconds = (unsigned long) ltime;
		nStartMilliSeconds *= 1000;
		_ftime64( &tstruct );
		nStartMilliSeconds += tstruct.millitm;        
		bFirstTime = false;
		nStartCount = nStartMilliSeconds;
	}

	_time64( &ltime );
	nMilliSeconds = (unsigned long) ltime;
	nMilliSeconds *= 1000;
	_ftime64( &tstruct );
	nMilliSeconds += tstruct.millitm;        
	bFirstTime = false;

	nMilliSeconds -= nStartMilliSeconds;
	//printf( "Plus milliseconds:%u\n",nMilliSeconds-nStartCount);

	double deltaTime = double(nMilliSeconds-nStartCount)/1000.0;
	nStartCount = nMilliSeconds;
	return deltaTime;

}