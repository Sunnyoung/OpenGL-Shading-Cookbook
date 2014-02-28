#pragma once
#include "scene.h"
#include "GLSLProgram.h"
#include "VBOTeapot.h"
#include <glm/glm.hpp>
using glm::mat4;
class SceneFog :
	public Scene
{
public:
	SceneFog(void);
	~SceneFog(void);
	void init();
	void reshape(int width, int height);
	void display();
private:
	GLSLProgram * mProgram;
	mat4 mModelView, mCamera, mProjection;
	VBOTeapot *mTeapot;
	float mAngle;
};

