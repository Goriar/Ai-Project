#pragma once

#define _USE_MATH_DEFINES
#include <math.h>
#include <stdlib.h>
#include <Windows.h>
#include <GL/GL.h>
#include <iostream>

#define EPSILON (0.000001)

#define CLAMP_VEC(v,m) { if (v.getLength() > m) {v.normalize(); v*= m;}}
#define CLAMP(a,b,c) { b = ((b) < (a))? (a) : (((b) > (c))? (c): (b));}

#define PIXEL_PER_METER      (1.0)
#define MAX_VELOCITY         (200.0)
#define MAX_ACCEL            (300.0)
#define MAX_ANGULAR_VELOCITY (30.0)
#define MAX_ANGULAR_ACCEL    (30.0)

#define DEG_TO_RAD(a) (a * M_PI / 180.0)
#define RAD_TO_DEG(a) (a * 180.0 / M_PI) 

#define VIEW_DISTANCE (500.0)
#define MAX_VIEW_FIELD_LENGTH (250.0)
#define MAX_ENERGY (30.0)
#define MIN_ENERGY (5.0)

#define NUMBER_OF_GHOSTS (6)
#define GHOST_PLAYER_DIST (120.0)

#define SURROUND_RADIUS (200.0)

#define VISIBLE_CIRCLE_RADIUS (100.0)


enum Tags { 
	NO_TAG,
	PLAYER_TAG,
	GHOST_TAG,
	OBSTACLE_TAG
};

enum Component_tag{
	NO_COMP_TAG,
	FOV,
	FOH,
	GHOST_BEH,
	MOVE,
	PLAYER,
	SPRITE
};

enum Ghost_state {
	IDLE,
	SEEK,
	FLEE
};


extern bool debug;

#ifdef _DEBUG
	#define DEBUG_MESSAGE(s) {std::cout << s << std::endl;}
#else
	#define DEBUG_MESSAGE(s) 
#endif
