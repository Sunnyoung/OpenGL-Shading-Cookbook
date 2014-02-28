#pragma once
#include "scene.h"
#include "GLSLProgram.h"
#include "VBOTeapot.h"
#include "VBOCube.h"
#include <glm/glm.hpp>
using glm::mat4;
class SceneTexture :
	public Scene{
public:
	SceneTexture(void);
	~SceneTexture(void);
	void init();
	void reshape(int width, int height);
	void display();

private:
	GLSLProgram *mProgram;
	mat4 mModelView, mCamera, mProjection;
	VBOTeapot *mTeapot;
	VBOCube *mCube;
	float mAngle;
	GLuint mTexID[2];
};

