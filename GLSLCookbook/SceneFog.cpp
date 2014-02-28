#include "SceneFog.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform2.hpp>
using namespace glm;

SceneFog::SceneFog(void) : mProgram(nullptr), mModelView(mat4(1.0)), mCamera(mat4(1.0)), mProjection(mat4(1.0)), mTeapot(nullptr), 
	mAngle(0){
}


SceneFog::~SceneFog(void){
	delete mTeapot;
	delete mProgram;
}

void SceneFog::init(){
	glClearColor(0, 0, 0, 1);
	glEnable(GL_DEPTH_TEST);

	mProgram = new GLSLProgram("fog.vert", "fog.frag");
	mTeapot = new VBOTeapot(mProgram, 14, mat4(1.0f), "VertexPosition", "VertexNormal", "VertexTex");

	mCamera = glm::lookAt(vec3(0.0f,4.0f,6.0f), vec3(0.0f,2.0f,0.0f), vec3(0.0f,1.0f,0.0f));

	mProgram->setUniform("light.intensity", vec3(0.9f,0.9f,0.9f) );
	mProgram->setUniform("fog.maxDist", 30.0f );
	mProgram->setUniform("fog.minDist", 1.0f );
	mProgram->setUniform("fog.color", vec3(0.5f,0.5f,0.5f) );
}

void SceneFog::reshape( int width, int height ){
	glViewport(0, 0, width, height);
	mProjection = glm::perspective(70.0f, float(width) / float(height), 0.1f, 100.0f);
}

void SceneFog::display(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	mModelView = mat4(1.0f);
	mModelView = mCamera * mModelView;
	increaseAngle(mAngle, 0.5f);
	float angle = TO_RADIANS(mAngle);
	vec4 lightPos = vec4(10.0f * cos(angle), 10.0f, 10.0f * sin(angle), 1.0f);
	mProgram->setUniform("light.position", mModelView * lightPos);

	mProgram->setUniform("Kd", 0.9f, 0.5f, 0.3f);
	mProgram->setUniform("Ka", 0.9f * 0.3f, 0.5f * 0.3f, 0.3f * 0.3f);
	mProgram->setUniform("Ks", 0.0f, 0.0f, 0.0f);
	mProgram->setUniform("Shininess", 180.0f);

	float dist = 0.0f;
	for( int i = 0 ; i < 4; i++ ) {
		mModelView = mat4(1.0f);
		mModelView = mCamera * mModelView;
		mModelView *= glm::translate(vec3(dist * 0.6f - 1.0f,0.0f,-dist));
		mModelView *= glm::rotate(-90.0f, vec3(1.0f,0.0f,0.0f));
		setUniformMatrix(mProgram, "MV", mModelView, "NM", "MVP", mProjection * mModelView);
		mTeapot->render();
		dist += 7.0f;
	}

	glutSwapBuffers();
	glutPostRedisplay();
}


