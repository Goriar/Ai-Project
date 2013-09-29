#include "app\AIWindow.h"
#include "core\Sprite.h"
#include "core\CharacterManager.h"
#include "core\Character.h"
#include <math.h>
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <sstream>

#include "components\MoveComponent.h"
#include "components\SpriteComponent.h"
#include "components\FieldOfHideComponent.h"
#include "components\ItemComponent.h"

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
#include "tasks\TaskRunInto.h"
#include "tasks\TaskWaitForAction.h"

using namespace BehaviourTree;

#include <sys\timeb.h>	
#include <time.h>



void AIWindow::createBehaviour() {

	for(int i = 0; i<NUMBER_OF_GHOSTS_TYPE1; ++i){
		behaviour1[i] = new Behaviour();
		Selector *huntSelector = new Selector(behaviour1[i]);
		Sequence *huntSequence = new Sequence(huntSelector);
		TaskSurroundPlayer *surround = new TaskSurroundPlayer(behaviour1[i],huntSequence,enemy1[i]);
		TaskPursuePlayer *pursue = new TaskPursuePlayer(behaviour1[i],huntSequence,enemy1[i]);
		TaskHideFromPlayer *hide = new TaskHideFromPlayer(behaviour1[i],huntSelector,enemy1[i]);
	}

	for(int i=0; i < NUMBER_OF_GHOSTS_TYPE2; ++i)
	{
		behaviour2[i] = new Behaviour();
		Selector *glotzSelector = new Selector(behaviour2[i]);
		Sequence *glotzSequence = new Sequence(glotzSelector);
		TaskWaitForAction *wait = new TaskWaitForAction(behaviour2[i], glotzSequence,enemy2[i]);
		TaskRunInto *runInto = new TaskRunInto(behaviour2[i],glotzSequence,enemy2[i]);
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
	createObstacle();
	createEnemys();
	createBehaviour();
	createItem();

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
}

void AIWindow::createItem(){
	CharacterManager *cm = CharacterManager::instance();
	int x,y;
	srand (time(NULL));
	x = rand()%nWidth;
	y = rand()%nHeight;
	item = cm->createCharacter("Item",ITEM_TAG,30.0);
	item->setPosition(CVector(x,y));

	while((cm->getNearestCharacter(item)->getPosition()-item->getPosition()).getLength() < 150){
		x = rand()%nHeight;
		y = rand()%nWidth;
		item->setPosition(CVector(x,y));
	}
	ItemComponent *itemComp = new ItemComponent(nWidth,nHeight,item);
	Sprite *sprite = new Sprite("..\\input\\tea.png");
	SpriteComponent *sc = new SpriteComponent(item,sprite);

}
void AIWindow::createObstacle(){
	CharacterManager *cm = CharacterManager::instance();
	double x = 0.0;
	double y = 0.0;
	srand (time(NULL));
	for (int i = 0; i <NUMBER_OF_OBSTACLES ; i++) {
		stringstream sstr;
		sstr << "Obstacle" << i;
		string obsName = sstr.str();
		obstacles[i] = cm->createCharacter(obsName,OBSTACLE_TAG);
		
		x = rand()%nWidth;
		y = rand()%nHeight;
		obstacles[i]->setPosition(CVector(x,y));
		while((cm->getNearestCharacter(obstacles[i])->getPosition()-obstacles[i]->getPosition()).getLength() < 150){
			x = rand()%nHeight;
			y = rand()%nWidth;
			obstacles[i]->setPosition(CVector(x,y));
		}

		FieldOfHideComponent *fohComponent = new FieldOfHideComponent(player, cm,obstacles[i]);

		Sprite *sp = new Sprite("..\\input\\wall.png");
		SpriteComponent *spc = new SpriteComponent(obstacles[i],sp);
	}
}

void AIWindow::createEnemys(){
	CharacterManager *cm = CharacterManager::instance();

	// enemey type 1
	for(int i = 0; i<NUMBER_OF_GHOSTS_TYPE1; ++i){
		stringstream sstr;
		sstr << "Ghost" << i;
		string ghostName = sstr.str();
		enemy1[i] = cm->createCharacter(ghostName, GHOST_TAG, 40.0);


		//generate random spawn point
		int w = rand()%nWidth;
		int h = rand()%nHeight;

		enemy1[i]->setPosition(CVector(w,h));
		while((cm->getNearestCharacter(enemy1[i])->getPosition()-enemy1[i]->getPosition()).getLength() < 150){
			w = rand()%nHeight;
			h = rand()%nWidth;
			enemy1[i]->setPosition(CVector(w,h));
		}

		Sprite *sprite = new Sprite("..\\input\\ghost.png");
		SpriteComponent *sc = new SpriteComponent(enemy1[i],sprite);

		// create a move component for it
		MoveComponent *mc = new MoveComponent(enemy1[i]);
		mc->setMaxVelocity(200.0);
		mc->setAngularSteering(new LookWhereYoureGoing());
	}

	// enemey type 2
	for(int i = 0; i<NUMBER_OF_GHOSTS_TYPE2; ++i){
		stringstream sstr;
		sstr << "GlotzGhost" << i;
		string ghostName = sstr.str();
		enemy2[i] = cm->createCharacter(ghostName, GHOST_TAG, 40.0);

		int w = rand()%nWidth;
		int h = rand()%nHeight;

		enemy2[i]->setPosition(CVector(w,h));
		while((cm->getNearestCharacter(enemy2[i])->getPosition()-enemy2[i]->getPosition()).getLength() < 150){
			w = rand()%nHeight;
			h = rand()%nWidth;
			enemy2[i]->setPosition(CVector(w,h));
		}

		Sprite *sprite = new Sprite("..\\input\\ghost2.png");
		SpriteComponent *sc = new SpriteComponent(enemy2[i],sprite);

		// create a move component for it
		MoveComponent *mc = new MoveComponent(enemy2[i]);
		mc->setMaxVelocity(200.0);
		mc->setAngularSteering(new LookWhereYoureGoing());
	}


}

void AIWindow::reset(){
	CharacterManager *cm = CharacterManager::instance();
	player->setPosition(CVector(nWidth/2,nHeight/2));
	getComponent<PlayerMoveComponent>(cm->getCharacter("Player"))->resetScore();
	
	int x = 0;
	int y = 0;
	for (int i = 0; i <NUMBER_OF_OBSTACLES ; i++) {
		x = rand()%nWidth;
		y = rand()%nHeight;
		obstacles[i]->setPosition(CVector(x,y));
		while((cm->getNearestCharacter(obstacles[i])->getPosition()-obstacles[i]->getPosition()).getLength() < 150){
			x = rand()%nHeight;
			y = rand()%nWidth;
			obstacles[i]->setPosition(CVector(x,y));
		}
	}

	// enemey type 1
	for(int i = 0; i<NUMBER_OF_GHOSTS_TYPE1; ++i){

		//generate random spawn point
		int w = rand()%nWidth;
		int h = rand()%nHeight;

		enemy1[i]->setPosition(CVector(w,h));
		while((cm->getNearestCharacter(enemy1[i])->getPosition()-enemy1[i]->getPosition()).getLength() < 150){
			w = rand()%nHeight;
			h = rand()%nWidth;
			enemy1[i]->setPosition(CVector(w,h));
		}
	}

	// enemey type 2
	for(int i = 0; i<NUMBER_OF_GHOSTS_TYPE2; ++i){

		int w = rand()%nWidth;
		int h = rand()%nHeight;

		enemy2[i]->setPosition(CVector(w,h));
		while((cm->getNearestCharacter(enemy2[i])->getPosition()-enemy2[i]->getPosition()).getLength() < 150){
			w = rand()%nHeight;
			h = rand()%nWidth;
			enemy2[i]->setPosition(CVector(w,h));
		}
	}

	x = rand()%nWidth;
	y = rand()%nHeight;
	item->setPosition(CVector(x,y));

	while((cm->getNearestCharacter(item)->getPosition()-item->getPosition()).getLength() < 150){
		x = rand()%nHeight;
		y = rand()%nWidth;
		item->setPosition(CVector(x,y));
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
	for(int i = 0; i < NUMBER_OF_GHOSTS_TYPE1; ++i){
		behaviour1[i]->update(timeDelta);}
	for(int i = 0; i < NUMBER_OF_GHOSTS_TYPE2; ++i){
		behaviour2[i]->update(timeDelta);}

	cm->draw();

	int score = getComponent<PlayerMoveComponent>(cm->getCharacter("Player"))->getScore();
	if(score>=10){
		reset();
	}
	stringstream ss;
	ss << "Score: " <<score;
	string s = ss.str();
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glDisable(GL_TEXTURE_2D);
	glColor3f(1.0f,1.0f,0.0f);
	glScalef(0.3f,0.3f,0.3f);
	glTranslatef(s.size(),30,0);
	for(int i = 0; i<s.size(); ++i){
		glutStrokeCharacter(GLUT_STROKE_ROMAN,s[i]);
	}
	glPopMatrix();
	glColor4d(1.0,1.0,1.0,1.0);

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