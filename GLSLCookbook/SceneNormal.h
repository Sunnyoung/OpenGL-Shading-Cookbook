#pragma once
#include "scene.h"
#include "GLSLProgram.h"
#include "VBOMesh.h"
#include <glm/glm.hpp>
using glm::mat4;
class SceneNormal :
	public Scene
{
public:
	SceneNormal(void);
	~SceneNormal(void);
	void init();
	void reshape(int width, int height);
	void display();
private:
	GLSLProgram *mProgram;
	mat4 mModelView, mCamera, mProjection;
	VBOMesh *mOrge;
};

