#pragma once
#include "scene.h"
#include "GLSLProgram.h"
#include "VBOTorus.h"
#include "VBOTeapot.h"
#include <glm/glm.hpp>
using glm::mat4;
class SceneSpotlight :
	public Scene
{
public:
	SceneSpotlight(void);
	~SceneSpotlight(void);
	void init();
	void reshape(int width, int height);
	void display();
	void keyboard(unsigned char key, int x,int y);
private:
	void incraseAngle(float step, float &angle);
private:
	GLSLProgram *mProgram;
	mat4 mModelView, mCamera, mProjection;
	VBOTorus *mTorus;
	VBOTeapot *mTeapot;
	float mAngle;
	int mIsSpot;
};

