#pragma once
#include "scene.h"
#include "GLSLProgram.h"
#include "VBOMesh.h"
#include <glm/glm.hpp>
using glm::mat3;
using glm::mat4;
class SceneMultiLight :
	public Scene{
public:
	SceneMultiLight(void);
	~SceneMultiLight(void);
	void init();
	void reshape(int width, int height);
	void display();
private:
	GLSLProgram *mProgram;
	mat4 mModelView, mCamera, mProjection;
	VBOMesh *mPig;
};

