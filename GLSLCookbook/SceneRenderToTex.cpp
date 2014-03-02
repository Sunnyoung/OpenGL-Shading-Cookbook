#include "SceneRenderToTex.h"
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform2.hpp>
using namespace std;
using namespace glm;

SceneRenderToTex::SceneRenderToTex(void) : mProgram(nullptr), mModel(mat4(1.0f)), mCamera(mat4(1.0f)), 
	mProjection(mat4(1.0f)), mCube(nullptr), mTeapot(nullptr), mFBO(0), mWidth(0), mHeight(0), mAngle(0.0f){
}


SceneRenderToTex::~SceneRenderToTex(void){
	delete mCube;
	delete mTeapot;
	delete mProgram;
}

void SceneRenderToTex::init(){
	glClearColor(0, 0, 0, 1);
	glEnable(GL_DEPTH_TEST);

	mProgram = new GLSLProgram("rendertotex.vert", "rendertotex.frag");
	mProgram->setDebug(true);
	mTeapot = new VBOTeapot(mProgram, 20, mat4(1.0f), "VertexPosition", "VertexNormal", "VertexTexCoord");
	mCube = new VBOCube(mProgram, "VertexPosition", "VertexNormal", "VertexTexCoord");

	mProgram->setUniform("LightIntensity", vec3(1.0f,1.0f,1.0f) );

	initFBO();

	// 创建一像素的白色纹理
	GLuint whiteTexHandle;
	GLubyte whiteTex[] = { 255, 255, 255, 255 };
	glActiveTexture(GL_TEXTURE1);
	glGenTextures(1, &whiteTexHandle);
	glBindTexture(GL_TEXTURE_2D,whiteTexHandle);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, whiteTex);
}

void SceneRenderToTex::initFBO(){
	//创建FBO
	glGenFramebuffers(1, &mFBO);
	glBindFramebuffer(GL_FRAMEBUFFER, mFBO);

	//创建一个纹理对象
	GLuint renderIndex;
	glGenTextures(1, &renderIndex);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, renderIndex);
	//glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGBA8, 512, 512);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 512, 512, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//纹理绑定到FBO
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, renderIndex, 0);

	// Create the depth buffer
	GLuint depthBuf;
	glGenRenderbuffers(1, &depthBuf);
	glBindRenderbuffer(GL_RENDERBUFFER, depthBuf);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, 512, 512);

	// Bind the depth buffer to the FBO
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT,
		GL_RENDERBUFFER, depthBuf);

	// Set the targets for the fragment output variables
	GLenum drawBuffers[] = {GL_COLOR_ATTACHMENT0};
	glDrawBuffers(1, drawBuffers);

	GLenum result = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	if( result == GL_FRAMEBUFFER_COMPLETE) {
		cout << "Framebuffer is complete" << endl;
	} else {
		cout << "Framebuffer error: " << result << endl;
	}

	// Unbind the framebuffer, and revert to default framebuffer
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void SceneRenderToTex::reshape( int width, int height ){
	glViewport(0, 0, width, height);
	mWidth = width;
	mHeight = height;
	mProjection = glm::perspective(70.0f, float(width) / float(height), 0.1f, 100.0f);
}

void SceneRenderToTex::renderToTexture(){
	mProgram->setUniform("RenderTex", 1);
	glViewport(0,0,512,512);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	mCamera = glm::lookAt(vec3(0.0f,0.0f,7.0f), vec3(0.0f,0.0f,0.0f), vec3(0.0f,1.0f,0.0f));
	mProjection = glm::perspective(60.0f, 1.0f, 0.3f, 100.0f);

	mProgram->setUniform("LightPosition", vec4(0.0f,0.0f,0.0f,1.0f) );
	mProgram->setUniform("Kd", 0.9f, 0.9f, 0.9f);
	mProgram->setUniform("Ks", 0.95f, 0.95f, 0.95f);
	mProgram->setUniform("Ka", 0.1f, 0.1f, 0.1f);
	mProgram->setUniform("Shininess", 100.0f);

	mModel = mat4(1.0f);
	mModel = glm::translate(mModel, vec3(0.0f,-1.5f,0.0f));
	mModel = glm::rotate(mModel, -90.0f, vec3(1.0f,0.0f,0.0f));
	setMatrix();
	mTeapot->render();
}

void SceneRenderToTex::renderToScene(){
	mProgram->setUniform("RenderTex", 0);
	glViewport(0,0, mWidth, mHeight);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	increaseAngle(mAngle, 0.05f);
	float angle = (float)TO_RADIANS(mAngle);
	vec3 cameraPos = vec3(2.0f * cos(angle), 1.5f, 2.0f * sin(angle));
	mCamera = glm::lookAt(cameraPos, vec3(0.0f,0.0f,0.0f), vec3(0.0f,1.0f,0.0f));

	mProjection = glm::perspective(45.0f, (float)mWidth/mHeight, 0.3f, 100.0f);

	mProgram->setUniform("LightPosition", vec4(0.0f,0.0f,0.0f,1.0f) );
	mProgram->setUniform("Kd", 0.9f, 0.9f, 0.9f);
	mProgram->setUniform("Ks", 0.0f, 0.0f, 0.0f);
	mProgram->setUniform("Ka", 0.1f, 0.1f, 0.1f);
	mProgram->setUniform("Shininess", 1.0f);

	mModel = mat4(1.0f);
	setMatrix();
	mCube->render();
}

void SceneRenderToTex::setMatrix(){
	mat4 mv = mCamera * mModel;
	mProgram->setUniform("MV", mv);
	mProgram->setUniform("NM",
		mat3( vec3(mv[0]), vec3(mv[1]), vec3(mv[2]) ));
	mProgram->setUniform("MVP", mProjection * mv);

}

void SceneRenderToTex::display(){
	glBindFramebuffer(GL_FRAMEBUFFER, mFBO);
	renderToTexture();

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	renderToScene();

	glutSwapBuffers();
	glutPostRedisplay();
}


