#include "Scene.h"
using namespace glm;

Scene::Scene(void){
}


Scene::~Scene(void)
{
}

void Scene::init(){

}

void Scene::reshape( int width, int height ){
	glViewport(0, 0, width, height);
}

void Scene::keyboard( unsigned char key, int x,int y ){

}

void Scene::keyboardUp( unsigned char key, int x, int y ){

}

void Scene::specialKey( int key, int x, int y ){

}

void Scene::specialKeyUp( int key, int x, int y ){

}

void Scene::setUniformMatrix( GLSLProgram *program, const string &MV, mat4 ModelView, const string &NM, const string &MVP, mat4 ModelViewProjection ){
	program->setUniform(MV.c_str(), ModelView);

	mat3 NormalMatrix = mat3(vec3(ModelView[0]), vec3(ModelView[1]), vec3(ModelView[2])); 
	program->setUniform(NM.c_str(), NormalMatrix);

	program->setUniform(MVP.c_str(), ModelViewProjection);
}

void Scene::increaseAngle( float &angle, float step ){
	angle += step;
	angle = angle > 360 ? angle - 360 : angle;
}
