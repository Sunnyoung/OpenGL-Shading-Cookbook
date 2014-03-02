#include "Scene.h"
#include "SceneBasic.h"
#include "SceneUniform.h"
#include "SceneDiffuse.h"
#include "SceneADS.h"
#include "SceneTwoSides.h"
#include "SceneMultiLight.h"
#include "SceneDirectional.h"
#include "ScenePerFragment.h"
#include "SceneHalfwayVector.h"
#include "SceneSpotlight.h"
#include "SceneCartoon.h"
#include "SceneFog.h"
#include "SceneTexture.h"
#include "SceneAlphaMap.h"
#include "SceneNormal.h"
#include "SceneCubeMap.h"
#include "SceneRefract.h"
#include "SceneProjectTexture.h"
#include "SceneRenderToTex.h"
#include <iostream>
using namespace std;

Scene *scene = new SceneRenderToTex();

void init(){
	scene->init();
}

void display(){
	scene->display();
}

void reshape(int width, int height){
	scene->reshape(width, height);
}

void keyboard(unsigned char key, int x, int y){
	scene->keyboard(key, x, y);
}

void keyboardUp(unsigned char key, int x, int y){
	scene->keyboardUp(key, x, y);
}

void specialKey(int key, int x, int y){
	scene->specialKey(key, x, y);
}

void specialKeyUp(int key, int x, int y){
	scene->specialKeyUp(key, x, y);
}

int main(int argc, char **argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_STENCIL);
	glutInitWindowSize(800, 600);
	glutCreateWindow("GLSL Scene");
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutKeyboardUpFunc(keyboardUp);
	glutSpecialFunc(specialKey);
	glutSpecialUpFunc(specialKeyUp);
	glutDisplayFunc(display);
	glFlush();
	GLenum err = glewInit();
	if (GLEW_OK != err) {
		fprintf(stderr, "GLEW Error: %s\n", glewGetErrorString(err));
		return 1;
	}
	init();
	glutMainLoop();
	return 0;
}