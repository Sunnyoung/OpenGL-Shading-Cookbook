#pragma once
#include "scene.h"
#include "GLSLProgram.h"
#include "VBOTeapot.h"
#include <glm/glm.hpp>
using glm::mat4;

class ScenePerFragment :
	public Scene{
public:
	ScenePerFragment(void);
	~ScenePerFragment(void);
	void init();
	void reshape(int width, int height);
	void display();
private:
	GLSLProgram *mProgram;
	mat4 mModelView, mCamera, mProjection;
	VBOTeapot *mTeapot;
	bool mIsDirectional;
	float mAngle;
};

