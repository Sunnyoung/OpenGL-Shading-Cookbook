#pragma once
#include "scene.h"
#include "GLSLProgram.h"
#include "VBOTorus.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform2.hpp>
class SceneDiffuse :
	public Scene{
public:
	SceneDiffuse(void);
	~SceneDiffuse(void);
	void init();
	void reshape(int width, int height);
	void display();
private:
	GLSLProgram *mProgram;
	VBOTorus *mTorus;
	glm::mat4 mModel;
	glm::mat4 mView;
	glm::mat4 mProjection;
};

