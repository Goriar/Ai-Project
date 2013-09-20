
#include "GlutWindow.h"

#include <math.h>
#include <GL/glut.h>
#include <sys/timeb.h>
#include <time.h>
#include <stdio.h>

#define DEG2RAD(a) ((a)/57.295)

#define ZOOMIN (0.05)
#define ZOOMAX (10.0)
//#define DISABLE_DRAGGING

GlutWindow::GlutWindow(void)
{

	nWidth = 1024;
	nHeight = 800;
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize (nWidth,nHeight); 
	glutInitWindowPosition (0, 0);
	glutCreateWindow ("Physics Window");
	
	initializeGL();

}

GlutWindow::~GlutWindow(void)
{
	
}


void GlutWindow::renderFrame() {

	// The usual OpenGL stuff to clear the screen and set up viewing.
	//glClearColor(.5, .5, 1., 1.);
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glViewport(0,0,nWidth,nHeight);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, nWidth, 0.0, nHeight, 0.0, 1.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glutSwapBuffers();
}


void GlutWindow::resize(int width, int height) {
	nWidth = width; 
	nHeight = height;
	glViewport(0, 0, (GLsizei) width, (GLsizei) height);

}

void GlutWindow::keyEvent(unsigned char key,int x,int y){
}

void GlutWindow::mouseButtonEvent(int button, int state,int x,int y){

	if (handleButtonEvent(button, state,x,y)) {
		return;
	}
}

void GlutWindow::mouseMoveEvent(int x,int y){
 
	if (handleMoveEvent(x,y)) {
		glutPostRedisplay();
	}
	return;
}

void GlutWindow::idle(){

	glutPostRedisplay();
}

void GlutWindow::initializeGL()
{
//  	glClearDepth(1.0f);
//glDepthFunc(GL_LESS);
//glEnable(GL_DEPTH_TEST);
}

bool GlutWindow::handleButtonEvent(int button, int state, int x, int y) {
	return false;
}

bool GlutWindow::handleMoveEvent(int x, int y) {
	return false;
}