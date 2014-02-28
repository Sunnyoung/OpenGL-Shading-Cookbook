#pragma once
#include "scene.h"
#include "VBOTorus.h"
#include "VBOTeapot.h"
#include "VBOMesh.h"
#include <glm/glm.hpp>
/************************************************************************/
/* 第2章的two sides、flat shading和discard shding 均由该类实现              */
/************************************************************************/
class SceneTwoSides :
	public Scene
{
public:
	SceneTwoSides(void);
	~SceneTwoSides(void);
	void init();
	void reshape(int width, int height);
	void display();
private:
	GLSLProgram *mProgram;
	VBOTeapot *mTeapot;
	VBOMesh *mOrge;
	glm::mat4 mModelView, mCamera, mProjection, mMVP;
	glm::mat3 mNMat;
	float mAngle;
};

