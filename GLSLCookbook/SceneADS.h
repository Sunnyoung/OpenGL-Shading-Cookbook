#pragma once
#include "scene.h"
#include "GLSLProgram.h"
#include "VBOTorus.h"
#include "VBOTeapot.h"
#include "VBOMesh.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform2.hpp>
class SceneADS :
	public Scene
{
public:
	SceneADS(void);
	~SceneADS(void);
	void init();
	void reshape(int width, int height);
	void display();
private:
	GLSLProgram *mProgram;
	VBOTorus *mTorus;
	VBOTeapot *mTeapot;
	VBOMesh *mMesh;
	glm::mat4 mModelView, mCamera, mProjection, mMVP;
	glm::mat3 mNMat;
	float mAngle;
};

