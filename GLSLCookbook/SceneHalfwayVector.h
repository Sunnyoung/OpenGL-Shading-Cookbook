#pragma once
#include "scene.h"
#include "GLSLProgram.h"
#include "VBOTeapot.h"
#include <glm/glm.hpp>
using glm::mat4;

class SceneHalfwayVector :
	public Scene
{
public:
	SceneHalfwayVector(void);
	~SceneHalfwayVector(void);
	void init();
	void reshape(int width, int height);
	void display();
	void keyboard(unsigned char key, int x,int y);
private:
	GLSLProgram *mProgram;
	mat4 mModelView, mCamera, mProjection;
	VBOTeapot *mTeapot;
	float mAngle;
	int mIsHalfway;
};

