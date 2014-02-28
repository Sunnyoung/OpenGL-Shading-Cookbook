#ifndef VBOCUBE_H
#define VBOCUBE_H
#include <string>
#include "GLSLProgram.h"
using std::string;
class VBOCube
{

private:
	GLSLProgram *mProgram;
    GLuint mVAO;

public:
    VBOCube(GLSLProgram *program, const string &vertexPos, const string &vertexNormal, const string &vertexTex);

    void render();
};

#endif // VBOCUBE_H
