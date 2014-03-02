#pragma once
#include "scene.h"
#include "GLSLProgram.h"
#include "VBOTeapot.h"
#include "VBOPlane.h"
#include "SkyBox.h"
#include "VBOTorus.h"
#include <glm/glm.hpp>
using glm::mat4;
class SceneRefract :
	public Scene
{
public:
	SceneRefract(void);
	~SceneRefract(void);
	void init();
	void reshape(int width, int height);
	void display();
	void keyboard(unsigned char key, int x,int y);
private:
	void loadCubeMap( const string &prefix );
	void setMatrix();
private:
	GLSLProgram *mProgram;
	mat4 mModel, mCamera, mProjection;
	VBOTeapot *mTeapot;
	VBOPlane *mPlane;
	SkyBox *mSkyBox;
	VBOTorus *mTorus;
	bool mDrawSkyBox;
};

