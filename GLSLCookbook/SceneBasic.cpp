#include "SceneBasic.h"


SceneBasic::SceneBasic(void){
}


SceneBasic::~SceneBasic(void){
}

void SceneBasic::init(){
	glClearColor(0, 0, 0, 1);

	mProgram = new GLSLProgram("shader/basic.vert", "shader/basic.frag");

	float positionData[] = {
		-0.8f, -0.8f, 0.0f,
		0.8f, -0.8f, 0.0f,
		0.0f,  0.8f, 0.0f 
	};
	float colorData[] = {
		1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 1.0f 
	};


	// Create and populate the buffer objects
	GLuint vbo[2];
	glGenBuffers(2, vbo);
	GLuint positionBufferHandle = vbo[0];
	GLuint colorBufferHandle = vbo[1];

	glBindBuffer(GL_ARRAY_BUFFER, positionBufferHandle);
	glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), positionData, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, colorBufferHandle);
	glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), colorData, GL_STATIC_DRAW);

	// Create and set-up the vertex array object
	glGenVertexArrays( 1, &mVAO );
	glBindVertexArray(mVAO);

	glEnableVertexAttribArray(0);  // Vertex position
	glEnableVertexAttribArray(1);  // Vertex color

	glBindBuffer(GL_ARRAY_BUFFER, positionBufferHandle);
	glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 0, nullptr );

	glBindBuffer(GL_ARRAY_BUFFER, colorBufferHandle);
	glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, 0, nullptr );
}

void SceneBasic::display(){
	glClear(GL_COLOR_BUFFER_BIT);
	glBindVertexArray(mVAO);
	glDrawArrays(GL_TRIANGLES, 0, 3);

	glutSwapBuffers();
	glutPostRedisplay();
}
