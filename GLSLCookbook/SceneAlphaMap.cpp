#include "SceneAlphaMap.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform2.hpp>
#include "TextureManager.h"
#include "TGAIO.h"
using namespace glm;

SceneAlphaMap::SceneAlphaMap(void) : mProgram(nullptr), mModelView(mat4(1.0f)), mCamera(mat4(1.0f)), mProjection(mat4(1.0f)), 
	mTeapot(nullptr), mCube(nullptr){
		for(int i = 0; i < 2; ++i)
			mTexID[i] = i;
}


SceneAlphaMap::~SceneAlphaMap(void){
	delete mTeapot;
	delete mCube;
	delete mProgram;
}

void SceneAlphaMap::init(){
	glClearColor(0, 0, 0, 1);
	glEnable(GL_DEPTH_TEST);

	mProgram = new GLSLProgram("alphamap.vert", "alphamap.frag");
	mProgram->setDebug(true);
	mTeapot = new VBOTeapot(mProgram, 14, mat4(1.0f), "VertexPosition", "VertexNormal", "VertexTexCoord");
	mCube = new VBOCube(mProgram, "VertexPosition", "VertexNormal", "VertexTexCoord");
	
	mCamera = glm::lookAt(vec3(0, 0, 6), vec3(0, 0, 0), vec3(0, 1, 0));
	
	glActiveTexture(GL_TEXTURE0);
	//TextureManager::Inst()->LoadTexture("texture/brick1.jpg", mTexID[0], GL_RGB, GL_RGB);
	//TextureManager::Inst()->LoadTexture("texture/cement.tga", mTexID[0], GL_RGBA8, GL_RGBA);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	TGAIO::loadTex("texture/cement.tga");

	glActiveTexture(GL_TEXTURE1);
	//TextureManager::Inst()->LoadTexture("texture/moss.tga", mTexID[1], GL_RGBA8, GL_RGBA);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	TGAIO::loadTex("texture/moss.tga");

	mProgram->setUniform("LightIntensity", vec3(1.0f, 1.0f, 1.0f));

	mProgram->setUniform("BaseTex", 0);
	mProgram->setUniform("AlphaTex", 1);

}

void SceneAlphaMap::reshape( int width, int height ){
	glViewport(0, 0, width, height);
	mProjection = glm::perspective(70.0f, float(width) / float(height), 0.1f, 100.0f);
}

void SceneAlphaMap::display(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	mModelView = mat4(1.0f);

	static float angle = 0;
	increaseAngle(angle, 0.05f);
	float radians = TO_RADIANS(angle);
	vec3 cameraPos = vec3(6.0f * cos(radians), 0.25f, 6.0f * sin(radians));
	mCamera = glm::lookAt(cameraPos, vec3(0.0f,0.0f,0.0f), vec3(0.0f,1.0f,0.0f));

	mModelView = mCamera * mModelView;

	mProgram->setUniform("LightPosition", vec4(0.0f,0.0f,0.0f,1.0f) );
	mProgram->setUniform("Kd", 0.9f, 0.9f, 0.9f);
	mProgram->setUniform("Ks", 0.9f, 0.9f, 0.9f);
	mProgram->setUniform("Ka", 0.1f, 0.1f, 0.1f);
	mProgram->setUniform("Shininess", 100.0f);

	mModelView = mat4(1.0f);
	mModelView = mCamera * mModelView;
	mModelView = glm::translate(mModelView, vec3(0.0f,-1.5f,0.0f));
	mModelView = glm::rotate(mModelView, -90.0f, vec3(1.0f,0.0f,0.0f));
	setUniformMatrix(mProgram, "MV", mModelView, "NM", "MVP", mProjection * mModelView);
	mTeapot->render();
	//mCube->render();

	glutSwapBuffers();
	glutPostRedisplay();
}






