#pragma once
#include "scene.h"
#include "GLSLProgram.h"
class SceneBasic :
	public Scene
{
public:
	SceneBasic(void);
	virtual ~SceneBasic(void);
	virtual void init();
	virtual void display();
private:
	GLSLProgram *mProgram;
	GLuint mVAO;
};

