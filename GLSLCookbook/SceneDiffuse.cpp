#include "SceneDiffuse.h"
using namespace glm;

SceneDiffuse::SceneDiffuse(void) : mProgram(nullptr), mTorus(nullptr){
}


SceneDiffuse::~SceneDiffuse(void){
	delete mProgram;
	delete mTorus;
}

void SceneDiffuse::init(){
	glClearColor(0, 0, 0, 1);
	glEnable(GL_DEPTH_TEST);

	mProgram = new GLSLProgram("diffuse.vert", "diffuse.frag");
	mTorus = new VBOTorus(mProgram, 0.7f, 0.3f, 30, 30, "VertexPosition", "VertexNormal", "VertexTex");

	mModel = mat4(1.0f);
	mModel *= glm::rotate(-35.0f, vec3(1.0f,0.0f,0.0f));
	mModel *= glm::rotate(35.0f, vec3(0.0f,1.0f,0.0f));
	mView = glm::lookAt(vec3(0.0f,0.0f,2.0f), vec3(0.0f,0.0f,0.0f), vec3(0.0f,1.0f,0.0f));
	mProjection = mat4(1.0f);

	mProgram->setUniform("Kd", vec3(0.9f, 0.5f, 0.3f));
	mProgram->setUniform("Ld", vec3(1.0f, 1.0f, 1.0f));
	mProgram->setUniform("LightPosition", mView * vec4(5.0f,5.0f,2.0f,1.0f));
}

void SceneDiffuse::reshape( int width, int height ){
	glViewport(0, 0, width, height);
	mProjection = glm::perspective(70.0f, (float)width/height, 0.3f, 100.0f);
}

void SceneDiffuse::display(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	mat4 mv = mView * mModel;
	mProgram->setUniform("ModelViewMatrix", mv);
	mProgram->setUniform("NormalMatrix",
		mat3( vec3(mv[0]), vec3(mv[1]), vec3(mv[2])));
	mProgram->setUniform("MVP", mProjection * mv);

	mTorus->render();

	glutSwapBuffers();
	glutPostRedisplay();
}



