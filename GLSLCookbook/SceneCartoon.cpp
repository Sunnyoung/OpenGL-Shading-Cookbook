#include "SceneCartoon.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform2.hpp>
using namespace glm;

SceneCartoon::SceneCartoon(void) : mProgram(nullptr), mModelView(mat4(1.0f)), mCamera(mat4(1.0f)), mProjection(mat4(1.0f)), 
	mTorus(nullptr), mTeapot(nullptr){
}


SceneCartoon::~SceneCartoon(void){
	delete mTorus;
	delete mTeapot;
	delete mProgram;
}

void SceneCartoon::init(){
	glClearColor(0, 0, 0, 1);
	glEnable(GL_DEPTH_TEST);

	mProgram = new GLSLProgram("cartoonshade.vert", "cartoonshade.frag");
	mTorus = new VBOTorus(mProgram, 0.7f, 0.4f, 50, 50, "VertexPosition", "VertexNormal", "VertexTex");
	mTeapot = new VBOTeapot(mProgram, 14, mat4(1.0f), "VertexPosition", "VertexNormal", "VertexTex");

	mCamera = glm::lookAt(vec3(4.0f,4.0f,6.5f), vec3(0.0f,0.75f,0.0f), vec3(0.0f,1.0f,0.0f));
	mProgram->setUniform("LightIntensity", vec3(0.9f, 0.9f, 0.9f));

}

void SceneCartoon::reshape( int width, int height ){
	glViewport(0, 0, width, height);
	mProjection = glm::perspective(70.0f, float(width) / float(height), 0.1f, 100.0f);
}

void SceneCartoon::display(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	mModelView = mat4(1.0f);
	mModelView = mCamera * mModelView;
	static float angle = 0;
	increaseAngle(angle, 0.5f);
	float radians = TO_RADIANS(angle);
	vec4 lightPos = vec4(10.0f * cos(radians), 10.0f, 10.0f * sin(radians), 1.0f);
	mProgram->setUniform("LightPosition", mModelView * lightPos);
	
	mProgram->setUniform("Kd", 0.9f, 0.5f, 0.3f);
	mProgram->setUniform("Ka", 0.9f * 0.3f, 0.5f * 0.3f, 0.3f * 0.3f);

	mModelView = mat4(1.0f);
	mModelView = mCamera * mModelView;
	mModelView *= glm::translate(vec3(0.0f,0.0f,-2.0f));
	mModelView *= glm::rotate(45.0f, vec3(0.0f,1.0f,0.0f));
	mModelView *= glm::rotate(-90.0f, vec3(1.0f,0.0f,0.0f));
	setUniformMatrix(mProgram, "MV", mModelView, "NM", "MVP", mProjection * mModelView);
	mTeapot->render();

	mProgram->setUniform("Kd", 0.9f, 0.5f, 0.3f);
	mProgram->setUniform("Ka", 0.9f * 0.3f, 0.5f * 0.3f, 0.3f * 0.3f);

	mModelView = mat4(1.0f);
	mModelView = mCamera * mModelView;
	mModelView *= glm::translate(vec3(-1.0f,0.75f,3.0f));
	mModelView *= glm::rotate(-90.0f, vec3(1.0f,0.0f,0.0f));
	setUniformMatrix(mProgram, "MV", mModelView, "NM", "MVP", mProjection * mModelView);
	mTorus->render();

	glutSwapBuffers();
	glutPostRedisplay();
}




