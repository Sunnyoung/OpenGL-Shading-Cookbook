#include "SceneADS.h"
using namespace glm;

SceneADS::SceneADS(void) : mProgram(nullptr), mTorus(nullptr), mTeapot(nullptr), mModelView(mat4(1.0f)), mAngle(0),
	mCamera(mat4(1.0f)), mProjection(mat4(1.0f)), mMVP(mat4(1.0f)), mNMat(mat3(1.0f)), mMesh(nullptr){
}


SceneADS::~SceneADS(void){
	delete mProgram;
	delete mTorus;
	delete mTeapot;
}

void SceneADS::init(){
	glClearColor(0, 0, 0, 1);
	glEnable(GL_DEPTH_TEST);

	mProgram = new GLSLProgram("ads.vert", "ads.frag");
	mProgram->use();
	mTorus = new VBOTorus(mProgram, 0.7f, 0.3f, 30, 30, "VertexPosition", "VertexNormal", "VertexTex");

	mat4 transform = glm::translate(mat4(1.0f),vec3(0.0f,1.5f,0.25f));
	mTeapot = new VBOTeapot(mProgram, 5, transform, "VertexPosition", "VertexNormal", "VertexTex");
	mCamera = glm::lookAt(vec3(0.0f,3.0f,5.0f), vec3(0.0f,0.75f,0.0f), vec3(0.0f,1.0f,0.0f));
	//mModelView = mCamera * mModelView;

	mProgram->setUniform("Ka", vec3(0.1f, 0.1f, 0.1f));
	mProgram->setUniform("Kd", vec3(0.9f, 0.5f, 0.3f));
	mProgram->setUniform("Ks", vec3(0.95f, 0.95f, 0.95f));

	mProgram->setUniform("La", vec3(0.9f, 0.9f, 0.9f));
	mProgram->setUniform("Ld", vec3(0.9f, 0.9f, 0.9f));
	mProgram->setUniform("Ls", vec3(0.9f, 0.9f, 0.9f));
	
	mProgram->setUniform("Shininess", 180.0f);
	mProgram->setUniform("LightPosition", mCamera * mModelView * vec4(0, 0, 0, 1));
}

void SceneADS::reshape( int width, int height ){
	glViewport(0, 0, width, height);
	mProjection = glm::perspective(75.0f, float(width)/float(height), 0.3f, 100.0f);
}

void SceneADS::display(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	mModelView = mat4(1.0f);
	mModelView = mCamera * mModelView;
	mAngle += 0.01f;
	mAngle = mAngle > 360 ? mAngle - 360 : mAngle;
	float radians = TO_RADIANS(mAngle);
	mProgram->setUniform("LightPosition", mModelView * vec4(10.0f * cos(radians), 3.0f, 10.0f * sin(radians), 1.0f));

	mModelView *= glm::translate(vec3(0.0f,0.0f,0.0f));
	mModelView *= glm::rotate(-90.0f, vec3(1.0f,0.0f,0.0f));
	setUniformMatrix(mProgram, "MV", mModelView, "NM", "MVP", mProjection * mModelView);
	mTeapot->render();

	glutSwapBuffers();
	glutPostRedisplay();
}



