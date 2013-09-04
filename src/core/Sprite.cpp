#include "core\Sprite.h"
#include <windows.h>
#include <GL\GL.h>

Sprite::Sprite(const char *filename) {

	// load the sprite
	loadTexture(filename);
}

void Sprite::loadTexture(const char *filename) {
	// load the textures
	glGenTextures(1,&texId);

	FILE *file = fopen(filename,"rb");
	unsigned short w;
	unsigned short h;
	unsigned char c;
	fread(&w,sizeof(unsigned short),1,file);
	fread(&h,sizeof(unsigned short),1,file);
	fread(&c,sizeof(unsigned char),1,file);

	int imgSize = w * h * c;
	unsigned char *imageBuffer = new unsigned char[imgSize];
	int readSize = fread(imageBuffer,sizeof(unsigned char),imgSize,file);
	if (imgSize != readSize) {
		exit(1);
	}
	fclose(file);

	GLenum format;
	switch(c) {
	case 1:
		format = GL_LUMINANCE;
		break;
	case 2:
		format = GL_LUMINANCE_ALPHA;
		break;
	case 3:
		format = GL_RGB;
		break;
	case 4:
		format = GL_RGBA;
		break;
	default:
		exit(-2);
	}

	glBindTexture(GL_TEXTURE_2D,texId);
	glTexImage2D(GL_TEXTURE_2D,0,format,w,h,0,format,GL_UNSIGNED_BYTE,imageBuffer);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);		
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);		

	delete [] imageBuffer;
}

void Sprite::bind() {

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,texId);

}