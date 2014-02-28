#pragma once
#include "scene.h"
#include "GLSLProgram.h"
#include "VBOTorus.h"
class SceneUniform :
	public Scene{
public:
	SceneUniform(void);
	virtual ~SceneUniform(void);
	virtual void init();
	virtual void display();
private:
	GLSLProgram *mProgram;
	GLuint mVAO;
	float mAngle;
	VBOTorus *mTorus;
};

