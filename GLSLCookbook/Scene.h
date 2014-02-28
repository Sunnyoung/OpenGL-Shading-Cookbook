#pragma once
#include "DEFINES.h"
#include "GLSLProgram.h"
#include <glm/glm.hpp>
#include <string>
using std::string;
using glm::mat3;
using glm::mat4;

class Scene{
public:
	Scene(void);
	virtual ~Scene(void);
	virtual void init();
	virtual void display() = 0;
	virtual void reshape(int width, int height);
	virtual void keyboard(unsigned char key, int x,int y);
	virtual void keyboardUp(unsigned char key, int x, int y);
	virtual void specialKey(int key, int x, int y);
	virtual void specialKeyUp(int key, int x, int y);
	virtual void setUniformMatrix(GLSLProgram *program, const string &MV, mat4 ModelView, const string &NM, const string &MVP, 
		mat4 ModelViewProjection);
	virtual void increaseAngle(float &angle, float step);
};

