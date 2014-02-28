#pragma once
#include "scene.h"
#include "GLSLProgram.h"
#include "VBOTorus.h"
#include <glm/glm.hpp>
using glm::mat3;
using glm::mat4;
class SceneDirectional :
	public Scene{
public:
	SceneDirectional(void);
	~SceneDirectional(void);
	void init();
	void reshape(int width, int height);
	void display();
	void keyboard(unsigned char key, int x,int y);
private:
	GLSLProgram *mProgram;
	mat4 mModelView, mCarema, mProjection;
	VBOTorus *mTorus;
	bool mIsDirectional;
};

