#pragma once
#include "scene.h"
#include "GLSLProgram.h"
#include "VBOTorus.h"
#include "VBOTeapot.h"
#include <glm/glm.hpp>
using glm::mat4;
class SceneCartoon :
	public Scene
{
public:
	SceneCartoon(void);
	~SceneCartoon(void);
	void init();
	void reshape(int width, int height);
	void display();
private:
	GLSLProgram *mProgram;
	mat4 mModelView, mCamera, mProjection;
	VBOTorus *mTorus;
	VBOTeapot *mTeapot;
};

