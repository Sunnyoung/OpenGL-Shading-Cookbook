#include "SceneSpotlight.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform2.hpp>
#include <iostream>
using namespace glm;
using namespace std;

SceneSpotlight::SceneSpotlight(void) : mProgram(nullptr), mModelView(mat4(1.0f)), mCamera(mat4(1.0f)), mProjection(mat4(1.0f)), 
	mTorus(nullptr), mTeapot(nullptr), mAngle(0), mIsSpot(TRUE){
}


SceneSpotlight::~SceneSpotlight(void){
	delete mTorus;
	delete mTeapot;
	delete mProgram;
}

void SceneSpotlight::init(){
	glClearColor(0, 0, 0, 1);
	glEnable(GL_DEPTH_TEST);

	mIsSpot ? cout << "¾Û¹âµÆ \n" : cout << "ÆÕÍ¨µÆ \n";

	mProgram = new GLSLProgram("spotlight.vert", "spotlight.frag");
	mTorus = new VBOTorus(mProgram, 1.75f * 0.75f, 0.75f * 0.75f, 50, 50, "VertexPosition", "VertexNormal", "VertexTex");
	mTeapot = new VBOTeapot(mProgram, 14, mat4(1.0f), "VertexPosition", "VertexNormal", "VertexTex");

	//mCamera = lookAt(vec3(0.0f,2.0f,0.5f), vec3(0.0f,1.75f,0.0f), vec3(0.0f,1.0f,0.0f));
	
	mCamera = glm::lookAt(vec3(5.0f,5.0f,7.5f), vec3(0.0f,0.75f,0.0f), vec3(0.0f,1.0f,0.0f));
	mProgram->setUniform("spotlight.intensity", vec3(0.9f, 0.9f, 0.9f));
	mProgram->setUniform("spotlight.exponent", 300.0f);
	mProgram->setUniform("spotlight.cutoff", 15.0f);

}

void SceneSpotlight::reshape( int width, int height ){
	glViewport(0, 0, width, height);
	mProjection = glm::perspective(70.0f, float(width) / float(height), 0.1f, 100.0f);
}

void SceneSpotlight::display(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	mProgram->setUniform("IsSpot", mIsSpot);
	mModelView = mat4(1.0f);
	mModelView = mCamera * mModelView;
	float angle = 0;
	incraseAngle(0.5f, angle);
	vec4 lightPos = vec4(10.0f * cos(angle), 10.0f, 10.0f * sin(angle), 1.0f);
	mProgram->setUniform("spotlight.position", mModelView * lightPos);
	mat3 NormalMatrix = mat3(vec3(mModelView[0]), vec3(mModelView[1]), vec3(mModelView[2]));
	mProgram->setUniform("spotlight.direction", NormalMatrix * vec3(-lightPos));
	
	mProgram->setUniform("Kd", 0.1f, 0.5f, 0.3f);
	mProgram->setUniform("Ks", 0.95f, 0.95f, 0.95f);
	mProgram->setUniform("Ka", 0.9f * 0.3f, 0.5f * 0.3f, 0.3f * 0.3f);
	mProgram->setUniform("Shininess", 100.0f);

	mModelView = mat4(1.0f);
	mModelView = mCamera * mModelView;
	mModelView *= glm::translate(vec3(0.0f,0.0f,-2.0f));
	mModelView *= glm::rotate(45.0f, vec3(0.0f,1.0f,0.0f));
	mModelView *= glm::rotate(-90.0f, vec3(1.0f,0.0f,0.0f));
	setUniformMatrix(mProgram, "MV", mModelView, "NM", "MVP", mProjection * mModelView);
	mTeapot->render();

	mProgram->setUniform("Kd", 0.9f, 0.5f, 0.9f);
	mProgram->setUniform("Ks", 0.95f, 0.95f, 0.95f);
	mProgram->setUniform("Ka", 0.9f * 0.3f, 0.5f * 0.3f, 0.3f * 0.3f);
	mProgram->setUniform("Shininess", 100.0f);

	mModelView = mat4(1.0f); 
	mModelView = mCamera * mModelView;
	mModelView *= glm::translate(vec3(-1.0f,0.75f,3.0f));
	mModelView *= glm::rotate(-90.0f, vec3(1.0f,0.0f,0.0f));
	setUniformMatrix(mProgram, "MV", mModelView, "NM", "MVP", mProjection * mModelView);
	mTorus->render();

	glutSwapBuffers();
	glutPostRedisplay();
}

void SceneSpotlight::keyboard( unsigned char key, int x,int y ){
	if(' ' == key)
		mIsSpot = !mIsSpot;
	mIsSpot ? cout << "¾Û¹âµÆ \n" : cout << "ÆÕÍ¨µÆ \n";
}

void SceneSpotlight::incraseAngle(float step, float &angle){
	mAngle += step;
	mAngle = mAngle > 360 ? mAngle - 360 : mAngle;
	angle = TO_RADIANS(mAngle);
}







