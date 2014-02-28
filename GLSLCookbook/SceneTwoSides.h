#pragma once
#include "scene.h"
#include "VBOTorus.h"
#include "VBOTeapot.h"
#include "VBOMesh.h"
#include <glm/glm.hpp>
/************************************************************************/
/* ��2�µ�two sides��flat shading��discard shding ���ɸ���ʵ��              */
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

