#include "SceneRefract.h"
#include "TGAIO.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform2.hpp>
using namespace glm;
SceneRefract::SceneRefract(void) : mProgram(nullptr), mModel(mat4(1.0f)), mCamera(mat4(1.0f)), mProjection(mat4(1.0f)),
	mTeapot(nullptr), mPlane(nullptr), mSkyBox(nullptr), mTorus(nullptr), mDrawSkyBox(true){
}


SceneRefract::~SceneRefract(void){
	delete mTeapot;
	delete mTorus;
	delete mPlane;
	delete mSkyBox;
	delete mProgram;
}

void SceneRefract::init(){
	glClearColor(0, 0, 0, 1);
	glEnable(GL_DEPTH_TEST);

	mProgram = new GLSLProgram("refract.vert", "refract.frag");
	mTeapot = new VBOTeapot(mProgram, 20, mat4(1.0f), "VertexPosition", "VertexNormal", "VertexTexCoord");
	mPlane = new VBOPlane(mProgram, 1.0f, 1.0f, 1, 1, "VertexPosition", "VertexNormal", "");
	mSkyBox = new SkyBox(mProgram->getProgram(), "VertexPosition");

	loadCubeMap("texture/cubemap_night/night");
}



const char * suffixes2[] = { "posx", "negx", "posy", "negy", "posz", "negz" };
GLuint targets2[] = {
	GL_TEXTURE_CUBE_MAP_POSITIVE_X, GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
	GL_TEXTURE_CUBE_MAP_POSITIVE_Y, GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
	GL_TEXTURE_CUBE_MAP_POSITIVE_Z, GL_TEXTURE_CUBE_MAP_NEGATIVE_Z
};
void SceneRefract::loadCubeMap( const string &prefix ){
	GLsizei w, h;
	for( int i = 0; i < 6; i++ ) {
		string texName = string(prefix.c_str()) + "_" + suffixes2[i] + ".tga";
		GLubyte * data = TGAIO::read(texName.c_str(), w, h);
		glTexImage2D(targets2[i], 0, GL_RGBA8, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		delete [] data;
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
}

void SceneRefract::reshape( int width, int height ){
	glViewport(0, 0, width, height);
	mProjection = glm::perspective(70.0f, float(width) / float(height), 0.1f, 100.0f);
}

void SceneRefract::display(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	static float angle = 0.0f;
	increaseAngle(angle, 0.05f);
	float radians = (float)TO_RADIANS(angle);
	vec3 cameraPos = vec3( 7.0f * cos(radians), 2.0f, 7.0f * sin(radians));
	mCamera = glm::lookAt(cameraPos, vec3(0.0f,0.0f,0.0f), vec3(0.0f,1.0f,0.0f));

	mProgram->setUniform("DrawSkyBox", mDrawSkyBox);
	mModel = mat4(1.0f);
	mSkyBox->render();

	mProgram->setUniform("DrawSkyBox", !mDrawSkyBox);
	mProgram->setUniform("RefractFactor", 0.1f);
	mProgram->setUniform("ReflectFactor", 0.9f);
	mModel = mat4(1.0f);
	mModel *= glm::translate(vec3(0.0f,-1.0f,0.0f));
	mModel *= glm::rotate(-90.0f, vec3(1.0f,0.0f,0.0f));
	setMatrix();
	mTeapot->render();

	glutSwapBuffers();
	glutPostRedisplay();
}

void SceneRefract::setMatrix(){
	mProgram->setUniform("M", mModel);
	mProgram->setUniform("MVP",mProjection * mCamera * mModel);
}

void SceneRefract::keyboard( unsigned char key, int x,int y ){
	if(' ' == key)
		mDrawSkyBox = !mDrawSkyBox;
}



