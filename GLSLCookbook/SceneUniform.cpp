#include "SceneUniform.h"
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include "DEFINES.h"
using namespace std;
SceneUniform::SceneUniform(void) : mAngle(0), mVAO(0), mProgram(nullptr){
}


SceneUniform::~SceneUniform(void){
}

float positions[] = {
	-0.8f, -0.8f, 0.0f,
	0.8f, -0.8f, 0.0f,
	0.0f,  0.8f, 0.0f
};

float colors[] = {
	1.0f, 0.0f, 0.0f,
	0.0f, 1.0f, 0.0f,
	0.0f, 0.0f, 1.0f 
};

void SceneUniform::init(){
	glClearColor(0, 0, 0 , 1);
	glEnable(GL_DEPTH_TEST);

	mProgram = new GLSLProgram("basicuniform.vert", "basicuniform.frag");
	mProgram->use();

	glGenVertexArrays(1, &mVAO);
	
	GLuint vbo[2];
	glGenBuffers(2, vbo);
	GLuint posBuf = vbo[0];
	GLuint colorBuf = vbo[1];
	
	glBindBuffer(GL_ARRAY_BUFFER, posBuf);
	glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), positions, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, colorBuf);
	glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), colors, GL_STATIC_DRAW);

	glGenVertexArrays(1, &mVAO);
	glBindVertexArray(mVAO);

	GLint posLoc = glGetAttribLocation(mProgram->getProgram(), "VertexPosition");
	GLint colorLoc = glGetAttribLocation(mProgram->getProgram(), "VertexColor");

	glEnableVertexAttribArray(posLoc);
	glEnableVertexAttribArray(colorLoc);

	glBindBuffer(GL_ARRAY_BUFFER, posBuf);
	glVertexAttribPointer(posLoc, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
	glBindBuffer(GL_ARRAY_BUFFER, colorBuf);
	glVertexAttribPointer(colorLoc, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
}

void SceneUniform::display(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::mat4 rotationMat = glm::rotate(glm::mat4(1.0f), mAngle, glm::vec3(1, 1, 0));
	//GLuint mvpLoc = glGetUniformLocation(mProgram, "mvp");
	//glUniformMatrix4fv(mvpLoc, 1, GL_FALSE, &rotationMat[0][0]);
	mProgram->setUniform("mvp", rotationMat);
	glBindVertexArray(mVAO);
	glDrawArrays(GL_TRIANGLES, 0, 3);

	mAngle += 0.2f;
	if(mAngle >= 360)
		mAngle -= 360;
	glutSwapBuffers();
	glutPostRedisplay();
}

