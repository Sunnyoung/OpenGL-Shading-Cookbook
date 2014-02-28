#include "SceneCubeMap.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform2.hpp>
#include "TGAIO.h"
#include <iostream>
using namespace std;
using namespace glm;
SceneCubeMap::SceneCubeMap(void) : mProgram(nullptr), mModel(mat4(1.0f)), mCamera(mat4(1.0f)), mProjection(mat4(1.0)), 
	mSkyBox(nullptr), mTexID(0), mDrawSkyBox(true){
}


SceneCubeMap::~SceneCubeMap(void){
	delete mSkyBox;
	delete mProgram;
}

void SceneCubeMap::init(){
	glClearColor(0, 0, 0, 1);
	glEnable(GL_DEPTH_TEST);

	mDrawSkyBox ? cout << "绘制天空盒\n" : cout << "不绘制天空盒\n";
	mProgram = new GLSLProgram("cubemap.vert", "cubemap.frag");

	mSkyBox = new SkyBox(mProgram->getProgram(), "VertexPosition");
	mTorus = new VBOTorus(mProgram, 0.7f, 0.3f, 50, 50, "VertexPosition", "VertexNormal", "VertexTexCoord");
	mTeapot = new VBOTeapot(mProgram, 15, mat4(1.0f), "VertexPosition", "VertexNormal", "VertexTexCoord");
	mPlane = new VBOPlane(mProgram, 1.0f, 1.0f, 1, 1, "VertexPosition", "VertexNormal", "VertexTexCoord");

	loadCubeMap("texture/cubemap_night/night");
}

const char * suffixes[] = { "posx", "negx", "posy", "negy", "posz", "negz" };
GLuint targets[] = {
	GL_TEXTURE_CUBE_MAP_POSITIVE_X, GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
	GL_TEXTURE_CUBE_MAP_POSITIVE_Y, GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
	GL_TEXTURE_CUBE_MAP_POSITIVE_Z, GL_TEXTURE_CUBE_MAP_NEGATIVE_Z
};
void SceneCubeMap::loadCubeMap( const string &prefix ){
	GLsizei w, h;
	for( int i = 0; i < 6; i++ ) {
		string texName = string(prefix.c_str()) + "_" + suffixes[i] + ".tga";
		GLubyte * data = TGAIO::read(texName.c_str(), w, h);
		glTexImage2D(targets[i], 0, GL_RGBA8, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		delete [] data;
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
}

void SceneCubeMap::reshape( int width, int height ){
	glViewport(0, 0, width, height);
	mProjection = glm::perspective(70.0f, float(width) / float(height), 0.1f, 100.0f);
}

void SceneCubeMap::display(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	static float angle = 0;
	increaseAngle(angle, 0.2f);
	float radians = (float)TO_RADIANS(angle);
	vec3 cameraPos = vec3( 7.0f * cos(radians), 2.0f, 7.0f * sin(radians));
	mCamera = glm::lookAt(cameraPos, vec3(0.0f,0.0f,0.0f), vec3(0.0f,1.0f,0.0f));
	
	mProgram->setUniform("WorldCameraPosition", cameraPos);
	mProgram->setUniform("DrawSkyBox", mDrawSkyBox);
	setMatrix("M", "MVP");
	mSkyBox->render();

	mProgram->setUniform("DrawSkyBox", !mDrawSkyBox);
	mProgram->setUniform("MaterialColor", vec4(0.5f, 0.5f, 0.5f, 1.0f));
	mProgram->setUniform("ReflectFactor", 0.85f);

	mModel = mat4(1.0f);
	mModel *= glm::translate(vec3(0.0f,-1.0f,0.0f));
	mModel *= glm::rotate(-90.0f, vec3(1.0f,0.0f,0.0f));
	setMatrix("M", "MVP");
	mTeapot->render();

	glutSwapBuffers();
	glutPostRedisplay();
}

void SceneCubeMap::setMatrix( const string &M, const string &MVP ){
	mProgram->setUniform("M", mModel);
	mProgram->setUniform("MVP", mProjection * mCamera * mModel);
}

void SceneCubeMap::keyboard( unsigned char key, int x,int y ){
	if(' ' == key)
		mDrawSkyBox = !mDrawSkyBox;
	mDrawSkyBox ? cout << "绘制天空盒\n" : cout << "不绘制天空盒\n";
}




