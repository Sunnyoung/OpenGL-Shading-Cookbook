#include "SceneMultiLight.h"
#include <string>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform2.hpp>

using namespace std;
using namespace glm;

SceneMultiLight::SceneMultiLight(void) : mProgram(nullptr), mModelView(mat4(1.0f)), mCamera(mat4(1.0f)),
	mProjection(mat4(1.0f)), mPig(nullptr){
}


SceneMultiLight::~SceneMultiLight(void){
	delete mPig;
	delete mProgram;
}

void SceneMultiLight::init(){
	glClearColor(0, 0, 0, 1);
	glEnable(GL_DEPTH_TEST);
	
	mProgram = new GLSLProgram("multilight.vert", "multilight.frag");

	//mCamera = glm::lookAt(vec3(5.5f,1.75f,0.75f), vec3(0.0f,0.0f,0.0f), vec3(0.0f,1.0f,0.0f));

	//mPig = new VBOMesh(mProgram, "pig_triangulated.obj", "VertexPosition", "VertexNormal", "VertexTexCoords", "VertexTangent", 
	//	"VertexEle");

	//char name[20];
	//for(int i = 0; i < 5; ++i){
	//	sprintf_s(name, "lights[%d].Position", i);
	//	float x = 2.0f * cosf((TWOPI_F / 5) * i);
	//	float z = 2.0f * sinf((TWOPI_F / 5) * i);
	//	mProgram->setUniform(name, mModelView * vec4(x, 1.2f, z + 1.0f, 1.0f) );
	//}

	//mProgram->setUniform("lights[0].Intensity", vec3(0.0f,0.8f,0.8f) );
	//mProgram->setUniform("lights[1].Intensity", vec3(0.0f,0.0f,0.8f) );
	//mProgram->setUniform("lights[2].Intensity", vec3(0.8f,0.0f,0.0f) );
	//mProgram->setUniform("lights[3].Intensity", vec3(0.0f,0.8f,0.0f) );
	//mProgram->setUniform("lights[4].Intensity", vec3(0.8f,0.8f,0.8f) );


	mPig = new VBOMesh(mProgram, "pig_triangulated.obj", "VertexPosition", "VertexNormal", "VertexTexCoords", "VertexTangent", 
		"VertexEle", true);

	mCamera = glm::lookAt(vec3(0.5f,0.75f,0.75f), vec3(0.0f,0.0f,0.0f), vec3(0.0f,1.0f,0.0f));
	mProjection = mat4(1.0f);

	char name[20];
	float x, z;
	for( int i = 0; i < 5; i++ ) {
		sprintf_s(name, "lights[%d].Position", i);
		x = 2.0f * cosf((TWOPI_F / 5) * i);
		z = 2.0f * sinf((TWOPI_F / 5) * i);
		mProgram->setUniform(name, mCamera * mModelView * vec4(x, 1.2f, z + 1.0f, 1.0f) );
	}

	mProgram->setUniform("lights[0].Intensity", vec3(0.0f,0.8f,0.8f) );
	mProgram->setUniform("lights[1].Intensity", vec3(0.0f,0.0f,0.8f) );
	mProgram->setUniform("lights[2].Intensity", vec3(0.8f,0.0f,0.0f) );
	mProgram->setUniform("lights[3].Intensity", vec3(0.0f,0.8f,0.0f) );
	mProgram->setUniform("lights[4].Intensity", vec3(0.8f,0.8f,0.8f) );
}

void SceneMultiLight::reshape( int width, int height ){
	glViewport(0, 0, width, height);
	mProjection = glm::perspective(70.0f, (float)width / (float)height, 0.3f, 100.0f);
}

void SceneMultiLight::display(){
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//mModelView = mat4(1.0f);
	//mModelView = mCamera * mModelView;
	//mProgram->setUniform("Kd", vec3(0.4f, 0.4f, 0.4f));
	//mProgram->setUniform("Ks", vec3(0.9f, 0.9f, 0.9f));
	//mProgram->setUniform("Ka", vec3(0.1f, 0.1f, 0.1f));
	//mProgram->setUniform("Shininess", 180.0f);

	//mModelView *= glm::translate(vec3(2.0f, 0.0f, 0.0f));
	//setUniformMatrix(mProgram, "MV", mModelView, "NM", "MVP", mProjection * mModelView);
	//mPig->render();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	mProgram->setUniform("Kd", vec3(0.4f, 0.4f, 0.4f));
	mProgram->setUniform("Ks", vec3(0.9f, 0.9f, 0.9f));
	mProgram->setUniform("Ka", vec3(0.1f, 0.1f, 0.1f));
	mProgram->setUniform("Shininess", 180.0f);

	mModelView = mat4(1.0f);
	mModelView = mCamera * mModelView;
	mModelView *= glm::rotate(90.0f, vec3(0.0f,1.0f,0.0f));
	setUniformMatrix(mProgram, "MV", mModelView, "NM", "MVP", mProjection * mModelView);
	mPig->render();

	glutSwapBuffers();
	glutPostRedisplay();
}








