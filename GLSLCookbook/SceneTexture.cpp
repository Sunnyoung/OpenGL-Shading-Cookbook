#include "SceneTexture.h"
#include "TextureManager.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform2.hpp>
#include <iostream>
using namespace glm;
using namespace std;

SceneTexture::SceneTexture(void) : mProgram(nullptr), mModelView(mat4(1.0)), mCamera(mat4(1.0)), mProjection(mat4(1.0)), mAngle(0), 
	mTeapot(nullptr), mCube(nullptr){
		for(int i = 0; i < 2; ++i)
			mTexID[i] = i;
}

SceneTexture::~SceneTexture(void){
	delete mCube;
	delete mTeapot;
	delete mProgram;
}

void SceneTexture::init(){
	glClearColor(0, 0, 0 ,1);
	glEnable(GL_DEPTH_TEST);

	mProgram = new GLSLProgram("alphamap.vert", "alphamap.frag");
	mProgram->setDebug(false);
	mTeapot = new VBOTeapot(mProgram, 14, mat4(1.0f), "VertexPosition", "VertexNormal", "VertexTexCoord");
	mCube = new VBOCube(mProgram, "VertexPosition", "VertexNormal", "VertexTexCoord");

	mCamera = glm::lookAt(vec3(1.0f,1.25f,1.25f), vec3(0.0f,0.0f,0.0f), vec3(0.0f,1.0f,0.0f));

	glActiveTexture(GL_TEXTURE0);
	TextureManager::Inst()->LoadTexture("texture/brick1.jpg", mTexID[0], GL_RGB, GL_RGB);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glActiveTexture(GL_TEXTURE1);
	TextureManager::Inst()->LoadTexture("texture/moss.png", mTexID[1], GL_RGBA, GL_RGBA);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	mProgram->setUniform("LightIntensity", vec3(1.0f,1.0f,1.0f) );
	mProgram->setUniform("BaseTex", 0);
	mProgram->setUniform("AlphaTex", 1);
}

void SceneTexture::reshape( int width, int height ){
	glViewport(0, 0, width, height);
	mProjection = glm::perspective(70.0f, float(width) / float(height), 0.1f, 100.0f);
}

void SceneTexture::display(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	mModelView = mat4(1.0f);
	mModelView = mCamera * mModelView;
	mProgram->setUniform("LightPosition", vec4(1.0f,0.0f,1.0f,1.0f));
	mProgram->setUniform("Kd", 0.9f, 0.9f, 0.9f);
	mProgram->setUniform("Ks", 0.95f, 0.95f, 0.95f);
	mProgram->setUniform("Ka", 0.1f, 0.1f, 0.1f);
	mProgram->setUniform("Shininess", 100.0f);

	static float angle = 0;
	increaseAngle(angle,0.5f);
	mModelView *= glm::rotate(angle, vec3(0, 1, 1));
	setUniformMatrix(mProgram, "MV", mModelView, "NM", "MVP", mProjection * mModelView);
	//TextureManager::Inst()->BindTexture(mTexID[0]);
	mCube->render();
	//mTeapot->render();

	glutSwapBuffers();
	glutPostRedisplay();
}



