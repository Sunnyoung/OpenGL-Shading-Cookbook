#pragma once
#include "scene.h"
#include "GLSLProgram.h"
#include "VBOPlane.h"
#include "VBOTeapot.h"
#include <glm/glm.hpp>
using glm::mat4;

class SceneProjectTexture :
	public Scene
{
public:
	SceneProjectTexture(void);
	~SceneProjectTexture(void);
	void init();
	void reshape(int width, int height);
	void display();
private:
	void setMatrix();
private:
	GLSLProgram *mProgram;
	mat4 mModel, mCamera, mProjection;
	VBOTeapot *mTeapot;
	VBOPlane *mPlane;

};

