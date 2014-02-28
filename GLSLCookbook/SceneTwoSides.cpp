#include "SceneTwoSides.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform2.hpp>
using namespace glm;

SceneTwoSides::SceneTwoSides(void) : mProgram(nullptr), mTeapot(nullptr), mModelView(mat4(1.0f)), mAngle(0),
	mCamera(mat4(1.0f)), mProjection(mat4(1.0f)), mMVP(mat4(1.0f)), mNMat(mat3(1.0f)){
}


SceneTwoSides::~SceneTwoSides(void){
	delete mTeapot;
	delete mOrge;
	delete mProgram;
}

void SceneTwoSides::init(){
	glClearColor(0, 0, 0, 1);
	glEnable(GL_DEPTH_TEST);

	mProgram = new GLSLProgram("discard.vert", "discard.frag");
	mProgram->use();

	mat4 transform = glm::translate(mat4(1.0f),vec3(0.0f,1.5f,0.25f));
	mTeapot = new VBOTeapot(mProgram, 14, transform, "VertexPosition", "VertexNormal", "VertexTexCoord");
	
	mOrge = new VBOMesh(mProgram, "pig_triangulated.obj", "VertexPosition", "VertexNormal", "VertexTexcoords", 
		"VertexTangent", "VertexEle");

	mCamera = glm::lookAt(vec3(0.0f,0.5f,4.0f), vec3(0.0f,-0.25f,0.0f), vec3(0.0f,1.0f,0.0f));

	mProgram->setUniform("Ka", vec3(0.9f, 0.5f, 0.3f));
	mProgram->setUniform("Kd", vec3(0.9f, 0.5f, 0.3f));
	mProgram->setUniform("Ks", vec3(0.8f, 0.8f, 0.8f));

	mProgram->setUniform("La", vec3(0.4f, 0.4f, 0.4f));
	mProgram->setUniform("Ld", vec3(1.0f, 1.0f, 1.0f));
	mProgram->setUniform("Ls", vec3(1.0f, 1.0f, 1.0f));

	mProgram->setUniform("Shininess", 100.0f);
}

void SceneTwoSides::reshape( int width, int height ){
	glViewport(0, 0, width, height);
	mProjection = glm::perspective(70.0f, float(width)/float(height), 0.3f, 100.0f);
}

void SceneTwoSides::display(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//vec4 worldLight = vec4(2.0f,4.0f,2.0f,1.0f);
	//mModelView = glm::rotate(0.0f, vec3(0.0f,1.0f,0.0f));
	//mProgram->setUniform("LightPosition", mCamera * mModelView * worldLight );

	//mAngle += 0.1f;
	//mAngle = mAngle > 360 ? mAngle- 360 : mAngle;
	//mModelView = mat4(1.0f);
	//mModelView = mCamera * mModelView;
	//mModelView *= glm::rotate(-40.0f, vec3(1.0f,0.0f,0.0f));

	vec4 worldLight = vec4(2.0f,4.0f,1.0f,1.0f);
	mModelView = glm::rotate(mAngle, vec3(0.0f,1.0f,0.0f));
	mProgram->setUniform("LightPosition", mCamera * mModelView * worldLight );

	mModelView = mat4(1.0f);
	mModelView = mCamera * mModelView;
	mModelView *= glm::rotate(90.0f, vec3(0.0f,1.0f,0.0f));

	mProgram->setUniform("MV", mModelView);
	mProgram->setUniform("NMat",
		mat3( vec3(mModelView[0]), vec3(mModelView[1]), vec3(mModelView[2]) ));
	mProgram->setUniform("MVP", mProjection * mModelView);
	//mTeapot->render();
	mOrge->render();

	glutSwapBuffers();
	glutPostRedisplay();
}


