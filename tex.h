#ifndef TEX_H
#define TEX_H
//-----------------------------------------------------------------------------
// Adapted from github open source code
// Reference to vivek2612, link: https://github.com/vivek2612/Human-Model-OpenGL
//-----------------------------------------------------------------------------

#include <FL/gl.h>
#include <FL/glut.H>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
using namespace std;

class Texture{
public:
	GLuint loadBMP_custom(const char * imagepath);
};

#endif