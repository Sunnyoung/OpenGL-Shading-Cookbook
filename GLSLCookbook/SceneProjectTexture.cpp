#include "SceneProjectTexture.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform2.hpp>
#include "TGAIO.h"
using namespace glm;

SceneProjectTexture::SceneProjectTexture(void) : mProgram(nullptr), mModel(mat4(1.0f)), mCamera(mat4(1.0f)), 
	mProjection(mat4(1.0)), mTeapot(nullptr), mPlane(nullptr){
}


SceneProjectTexture::~SceneProjectTexture(void){
	delete mPlane;
	delete mTeapot;
	delete mProgram;
}

void SceneProjectTexture::init(){
	glClearColor(0, 0, 0, 1);
	glEnable(GL_DEPTH_TEST);

	mProgram = new GLSLProgram("projecttexture.vert", "projecttexture.frag");
	mProgram->setDebug(true);
	mTeapot = new VBOTeapot(mProgram, 20, mat4(1.0f), "VertexPosition", "VertexNormal", "");
	mPlane = new VBOPlane(mProgram, 100.0f, 100.0f, 1, 1, "VertexPosition", "VertexNormal", "");


	vec3 projPos = vec3(2.0f,5.0f,5.0f);
	vec3 projAt = vec3(-2.0f,-4.0f,0.0f);
	vec3 projUp = vec3(0.0f,1.0f,0.0f);
	mat4 projView = glm::lookAt(projPos, projAt, projUp);//Í¶Ó°ÒÇÎ»ÖÃ
	mat4 projProj = glm::perspective(30.0f, 1.0f, 0.2f, 1000.0f);
	mat4 projScaleTrans = glm::translate(vec3(0.0f)) * glm::scale(vec3(0.5f));
	mProgram->setUniform("ProjectorMatrix", projScaleTrans * projProj * projView);
	//mProgram->setUniform("ProjectorMatrix", projProj * projView);

	glActiveTexture(GL_TEXTURE0);
	TGAIO::loadTex("texture/flower.tga");
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

	mProgram->setUniform("LightPosition", vec4(0.0f,0.0f,0.0f,1.0f) );
	mProgram->setUniform("LightIntensity", vec3(1.0f,1.0f,1.0f));
}

void SceneProjectTexture::reshape( int width, int height ){
	glViewport(0, 0, width, height);
	mProjection = glm::perspective(70.0f, float(width) / float(height), 0.1f, 100.0f);
}

void SceneProjectTexture::display(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	static float angle = 0.0f;
	increaseAngle(angle, 0.05f);
	float radians = (float)TO_RADIANS(angle);
	vec3 cameraPos = vec3( 7.0f * cos(radians), 2.0f, 7.0f * sin(radians));
	mCamera = glm::lookAt(cameraPos, vec3(0.0f,0.0f,0.0f), vec3(0.0f,1.0f,0.0f));

	mProgram->setUniform("Kd", 0.5f, 0.2f, 0.1f);
	mProgram->setUniform("Ks", 0.95f, 0.95f, 0.95f);
	mProgram->setUniform("Ka", 0.1f, 0.1f, 0.1f);
	mProgram->setUniform("Shininess", 100.0f);

	mModel = mat4(1.0f);
	mModel *= glm::translate(vec3(0.0f,-1.0f,0.0f));
	mModel *= glm::rotate(-90.0f, vec3(1.0f,0.0f,0.0f));
	setMatrix();
	mTeapot->render();

	mProgram->setUniform("Kd", 0.4f, 0.4f, 0.4f);
	mProgram->setUniform("Ks", 0.0f, 0.0f, 0.0f);
	mProgram->setUniform("Ka", 0.1f, 0.1f, 0.1f);
	mProgram->setUniform("Shininess", 1.0f);
	mModel = mat4(1.0f);
	mModel *= glm::translate(vec3(0.0f,-0.75f,0.0f));
	//mModel *= glm::rotate(15.0f, vec3(1, 0, 0));
	setMatrix();
	mPlane->render();

	glutSwapBuffers();
	glutPostRedisplay();
}

void SceneProjectTexture::setMatrix(){
	mat4 mv = mCamera * mModel;
	mProgram->setUniform("M", mModel);
	mProgram->setUniform("MV", mv);
	mProgram->setUniform("NM",
		mat3( vec3(mv[0]), vec3(mv[1]), vec3(mv[2]) ));
	mProgram->setUniform("MVP", mProjection * mv);
}


