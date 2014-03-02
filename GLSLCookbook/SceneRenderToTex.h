#pragma once
#include "scene.h"
#include "GLSLProgram.h"
#include "VBOTeapot.h"
#include "VBOCube.h"
#include <glm/glm.hpp>
using glm::mat4;
class SceneRenderToTex :
	public Scene
{
public:
	SceneRenderToTex(void);
	~SceneRenderToTex(void);
	void init();
	void reshape(int width, int height);
	void display();
private:
	void initFBO();
	void renderToTexture();
	void renderToScene();
	void setMatrix();
private:
	GLSLProgram *mProgram;
	mat4 mModel, mCamera, mProjection;
	VBOCube *mCube;
	VBOTeapot *mTeapot;
	GLuint mFBO;
	GLsizei mWidth, mHeight;
	float mAngle;
};

