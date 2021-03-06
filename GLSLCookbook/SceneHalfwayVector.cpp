#include "SceneHalfwayVector.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform2.hpp>
#include <iostream>
using namespace glm;
using namespace std;

SceneHalfwayVector::SceneHalfwayVector(void) : mProgram(nullptr), mModelView(mat4(1.0f)), mCamera(mat4(1.0f)), 
	mProjection(mat4(1.0f)), mTeapot(nullptr), mAngle(0), mIsHalfway(TRUE){
}


SceneHalfwayVector::~SceneHalfwayVector(void){
	delete mTeapot;
	delete mProgram;
}

void SceneHalfwayVector::init(){
	glClearColor(0, 0, 0, 1);
	glEnable(GL_DEPTH_TEST);

	//mProgram = new GLSLProgram("perfragment.vert", "perfragment.frag"); //片元光照模型 Phong
	//mProgram = new GLSLProgram("directional.vert", "directional.frag"); //顶点光照模型 Gouraud
	mProgram = new GLSLProgram("halfwayvector.vert", "halfwayvector.frag");
	mTeapot = new VBOTeapot(mProgram, 13, mat4(1.0), "VertexPosition", "VertexNormal", "VertexTex");

	mCamera = glm::lookAt(vec3(0.0f,3.0f,5.0f), vec3(0.0f,0.75f,0.0f), vec3(0.0f,1.0f,0.0f));

	mProgram->setUniform("LightIntensity", vec3(0.9f, 0.9f, 0.9f));

	mProgram->setUniform("Ka", vec3(0.1f, 0.1f, 0.1f));
	mProgram->setUniform("Kd", vec3(0.9f, 0.5f, 0.3f));
	mProgram->setUniform("Ks", vec3(0.95f, 0.95f, 0.95f));
	mProgram->setUniform("Shininess", 100.0f);
}

void SceneHalfwayVector::reshape( int width, int height ){
	glViewport(0, 0, width, height);
	mProjection = glm::perspective(70.0f, float(width) / float(height), 0.1f, 100.0f);
}

void SceneHalfwayVector::display(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	mModelView = mat4(1.0f);
	mModelView = mCamera * mModelView;
	//mModelView *= glm::rotate(90.0f, vec3(0.0f, 1.0f, 0.0f));
	mAngle += 0.05f;
	mAngle = mAngle > 360 ? mAngle - 360 : mAngle;
	float radians = TO_RADIANS(mAngle);
	mProgram->setUniform("LightPosition", mModelView * vec4(10.0f * cos(radians), 3.0f, 10.0f * sin(radians), 1.0f));
	mProgram->setUniform("Halfway", mIsHalfway);

	mModelView *= glm::translate(vec3(0.0f,0.0f,0.0f));
	mModelView *= glm::rotate(-90.0f, vec3(1.0f,0.0f,0.0f));
	setUniformMatrix(mProgram, "MV", mModelView, "NM", "MVP", mProjection * mModelView);
	mTeapot->render();

	glutSwapBuffers();
	glutPostRedisplay();
}

void SceneHalfwayVector::keyboard( unsigned char key, int x,int y ){
	if(' ' == key)
		mIsHalfway = !mIsHalfway;
}