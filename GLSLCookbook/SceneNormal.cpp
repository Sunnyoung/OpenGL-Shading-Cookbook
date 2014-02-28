#include "SceneNormal.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include "TGAIO.h"
using namespace glm;
SceneNormal::SceneNormal(void) : mProgram(nullptr), mModelView(mat4(1.0f)), mCamera(mat4(1.0f)), mProjection(mat4(1.0f)), 
	mOrge(nullptr){
}


SceneNormal::~SceneNormal(void){
}

void SceneNormal::init(){
	glClearColor(0, 0, 0, 1);
	glEnable(GL_DEPTH_TEST);

	mProgram = new GLSLProgram("normalmap.vert", "normalmap.frag");
	mOrge = new VBOMesh(mProgram, "bs_ears.obj", "VertexPosition", "VertexNormal", "VertexTexCoord", "VertexTangent", "",false, true, true);
	mCamera = glm::lookAt(vec3(-1.0f,0.25f,2.0f), vec3(0.0f,0.0f,0.0f), vec3(0.0f,1.0f,0.0f));

	// Load diffuse texture
	glActiveTexture(GL_TEXTURE0);
	TGAIO::loadTex("texture/ogre_diffuse.tga");

	// Load normal map
	glActiveTexture(GL_TEXTURE1);
	TGAIO::loadTex("texture/ogre_normalmap.tga");

	mProgram->setUniform("LightIntensity", vec3(0.9f,0.9f,0.9f) );
	mProgram->setUniform("ColorTex", 0);
	mProgram->setUniform("NormalMapTex", 1);

}

void SceneNormal::reshape( int width, int height ){
	glViewport(0, 0, width, height);
	mProjection = glm::perspective(70.0f, float(width) / float(height), 0.1f, 100.0f);
}

void SceneNormal::display(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	static float angle = 0.0f;
	increaseAngle(angle, 0.2f);
	float radians = (float)TO_RADIANS(angle);
	mProgram->setUniform("LightPosition", mCamera * vec4(10.0f * cos(radians),1.0f,10.0f * sin(radians),1.0f) );
	mProgram->setUniform("Ks", 0.2f, 0.2f, 0.2f);
	mProgram->setUniform("Ka", 0.1f, 0.1f, 0.1f);
	mProgram->setUniform("Shininess", 1.0f);

	mModelView = mat4(1.0f);
	mModelView = mCamera * mModelView;
	setUniformMatrix(mProgram, "MV", mModelView, "NM", "MVP", mProjection * mModelView);
	mOrge->render();

	glutSwapBuffers();
	glutPostRedisplay();
}








