#include "SceneDirectional.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform2.hpp>
#include <iostream>
using namespace glm;
using namespace std;

SceneDirectional::SceneDirectional(void) : mProgram(nullptr), mModelView(mat4(1.0f)), mCarema(mat4(1.0f)), 
	mProjection(mat4(1.0f)), mTorus(nullptr), mIsDirectional(true){
}


SceneDirectional::~SceneDirectional(void){
	delete mTorus;
	delete mProgram; 
}

vec4 LightPositionDir = vec4(1, 0, 0, 0);
vec4 LightPositionPnt = vec4(1, 0, 0, 1);
vec3 LightIntensity = vec3(0.8f, 0.8f, 0.8f);
void SceneDirectional::init(){
	mIsDirectional ? cout << "向光源\n" : cout <<"点光源\n";

	glClearColor(0, 0, 0, 1);
	glEnable(GL_DEPTH_TEST);

	mProgram = new GLSLProgram("directional.vert", "directional.frag");
	mTorus = new VBOTorus(mProgram, 0.8f, 0.3f, 40, 40, "VertexPosition", "VertexNormal", "VertexTex" );

	mCarema = glm::lookAt(vec3(1, 1, 1.2f), vec3(0, 0, 0), vec3(0, 1, 0));

	mProgram->setUniform("LightPosition", mIsDirectional ? LightPositionDir : LightPositionPnt);
	mProgram->setUniform("LightIntensity", LightIntensity);

	mProgram->setUniform("Ka", vec3(0.1f, 0.1f, 0.1f));
	mProgram->setUniform("Kd", vec3(0.8f, 0.8f, 0.8f));
	mProgram->setUniform("Ks", vec3(0.9f, 0.9f, 0.9f));
	mProgram->setUniform("Shininess", 100.0f);
}

void SceneDirectional::reshape( int width, int height ){
	glViewport(0, 0, width, height);
	mProjection = glm::perspective(70.0f, float(width) / float(height), 0.1f, 100.0f);
}

void SceneDirectional::display(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	mModelView = mat4(1.0f);
	mModelView = mCarema * mModelView;
	mModelView *= glm::rotate(90.0f, vec3(0.0f, 1.0f, 0.0f));
	mProgram->setUniform("LightPosition", mIsDirectional ? mModelView * LightPositionDir : mModelView * LightPositionPnt);
	setUniformMatrix(mProgram, "MV", mModelView, "NM", "MVP", mProjection * mModelView);
	mTorus->render();

	glutSwapBuffers();
	glutPostRedisplay();
}

void SceneDirectional::keyboard( unsigned char key, int x,int y ){
	if(' ' == key)
		mIsDirectional = !mIsDirectional;
	mIsDirectional ? cout << "向光源\n" : cout <<"点光源\n";
}







