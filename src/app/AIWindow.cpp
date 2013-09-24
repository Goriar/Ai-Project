#include "app\AIWindow.h"
#include "core\Sprite.h"
#include "core\CharacterManager.h"
#include "core\Character.h"
#include <math.h>
#include <GL/glut.h>
#include <stdio.h>
#include <assert.h>
#include <sstream>

#include "components\MoveComponent.h"
#include "components\SpriteComponent.h"
#include "components\FieldOfHideComponent.h"
#include "components\GhostBehaviourComponent.h"

#include "behaviour\Behaviour.h"
#include "behaviour\Sequence.h"
#include "behaviour\Selector.h"

#include "steering\LookWhereYoureGoing.h"
#include "steering\Wander.h"
#include "steering\Flee.h"
#include "steering\Seek.h"
#include "steering\Idle.h"

#include "tasks\TaskHideFromPlayer.h"
#include "tasks\TaskPursuePlayer.h"
#include "tasks\TaskSurroundPlayer.h"

using namespace BehaviourTree;

#include <sys\timeb.h>	
#include <time.h>



void AIWindow::createBehaviour() {


	for(int i = 0; i<NUMBER_OF_GHOSTS; ++i){
		behaviour[i] = new Behaviour();
		Selector *huntSelector = new Selector(behaviour[i]);
		Sequence *huntSequence = new Sequence(huntSelector);
		TaskSurroundPlayer *surround = new TaskSurroundPlayer(behaviour[i],huntSequence,enemy[i]);
		TaskPursuePlayer *pursue = new TaskPursuePlayer(behaviour[i],huntSequence,enemy[i]);
		TaskHideFromPlayer *hide = new TaskHideFromPlayer(behaviour[i],huntSelector,enemy[i]);
	}

}


AIWindow::AIWindow()
{
	dragCharacter = NULL;
	bDragging = false;
	keyStates = new bool[256];
	memset(keyStates,0,256);
	fov = new CVector();

	createPlayer();
	createEnemy();
	createBehaviour();

	glClearColor(0.0, 0.0, 0.0, 1.0);
	srand(time(0));
}

AIWindow::~AIWindow(void)
{
	
}

void AIWindow::createPlayer(){
	CharacterManager *cm = CharacterManager::instance();
	player = cm->createCharacter("Player",PLAYER_TAG);
	player->setPosition(CVector(nWidth/2,nHeight/2));

	PlayerMoveComponent *pMovComp = new PlayerMoveComponent(keyStates,player);
	FieldOfViewComponent *fovComponent = new FieldOfViewComponent(fov,player);

	Sprite *sprite = new Sprite("..\\input\\gentleman.png");
	SpriteComponent *sc = new SpriteComponent(player,sprite);



	double x = 0.0;
	double y = 0.0;
	//srand (time(NULL));
	for (int i = 0; i <5 ; i++) {
		Character *obstacles = NULL;
		stringstream sstr;
		sstr << "Obstacle" << i;
		string obsName = sstr.str();
		obstacles = cm->createCharacter(obsName,OBSTACLE_TAG);
		
		x = rand()%nWidth;
		y = rand()%nHeight;
		obstacles->setPosition(CVector(x,y));

		FieldOfHideComponent *fohComponent = new FieldOfHideComponent(player, cm,obstacles);

		Sprite *sp = new Sprite("..\\input\\wall.png");
		SpriteComponent *spc = new SpriteComponent(obstacles,sp);
	}
}

void AIWindow::createEnemy(){
	CharacterManager *cm = CharacterManager::instance();

	for(int i = 0; i<NUMBER_OF_GHOSTS; ++i){
		stringstream sstr;
		sstr << "Ghost" << i;
		string ghostName = sstr.str();
		enemy[i] = cm->createCharacter(ghostName, GHOST_TAG, 40.0);

		//generate random spawn point
		
		int w = rand()%nWidth;
		int h = 400;

		enemy[i]->setPosition(CVector(w,h));

		Sprite *sprite = new Sprite("..\\input\\ghost.png");
		SpriteComponent *sc = new SpriteComponent(enemy[i],sprite);

		// create a move component for it
		MoveComponent *mc = new MoveComponent(enemy[i]);
		mc->setMaxVelocity(200.0);
		mc->setAngularSteering(new LookWhereYoureGoing());
		//mc->setPositionSteering(new Seek(cm->getCharacter("Player")));

		//GhostBehaviourComponent *ghostBehaviour = new GhostBehaviourComponent(enemy, mc, cm, GHOST_BEH);
	}

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
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	double timeDelta = getTimeDelta();

	CharacterManager *cm = CharacterManager::instance();
	
	cm->update(timeDelta);
	for(int i = 0; i < NUMBER_OF_GHOSTS; ++i){
		behaviour[i]->update(timeDelta);
		
	}

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

	if(key == '1')
		debug = !debug;
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