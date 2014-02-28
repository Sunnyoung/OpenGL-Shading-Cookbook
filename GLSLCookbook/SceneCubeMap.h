#pragma once
#include "scene.h"
#include "GLSLProgram.h"
#include "SkyBox.h"
#include <glm/glm.hpp>
#include <string>
#include "VBOTorus.h"
#include "VBOTeapot.h"
#include "VBOPlane.h"
using std::string;
using glm::mat4;
class SceneCubeMap :
	public Scene{
public:
	SceneCubeMap(void);
	~SceneCubeMap(void);
	void init();
	void reshape(int width, int height);
	void display();
	void keyboard(unsigned char key, int x,int y);
private:
	void loadCubeMap(const string &prefix);
	void setMatrix(const string &M, const string &MVP);
private:
	GLSLProgram *mProgram;
	mat4 mModel, mCamera, mProjection;
	SkyBox *mSkyBox;
	VBOTorus *mTorus;
	VBOTeapot *mTeapot;
	VBOPlane *mPlane;
	GLuint mTexID;
	bool mDrawSkyBox;
};

