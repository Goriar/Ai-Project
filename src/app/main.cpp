// TerraGen.cpp : Defines the entry point for the console application.
//

#include "app\AIWindow.h"
#include <GL/glut.h>
#include <time.h>

bool debug = true;

AIWindow *g_pMainWindow = 0;

void display(void)                              { g_pMainWindow->renderFrame();}
void idle(void)                                 { g_pMainWindow->idle();}
void reshape(int width, int height)             { g_pMainWindow->resize(width, height);}
void keyboard(unsigned char key, int x, int y)  { g_pMainWindow->keyEvent(key,x,y);}
void keyboardUp(unsigned char key, int x, int y)  { g_pMainWindow->keyUpEvent(key,x,y);}
void mouse(int button, int state, int x, int y) { g_pMainWindow->mouseButtonEvent(button, state,x,y);}
void move(int x, int y)                         { g_pMainWindow->mouseMoveEvent(x,y);}


int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
 
	g_pMainWindow = new AIWindow();
	glutDisplayFunc(display); 
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
	glutKeyboardUpFunc(keyboardUp);
    glutMouseFunc(mouse);
    glutMotionFunc(move);
    glutPassiveMotionFunc(move);
	glutIdleFunc(idle);
	glutMainLoop();
	

	return 0;
}
