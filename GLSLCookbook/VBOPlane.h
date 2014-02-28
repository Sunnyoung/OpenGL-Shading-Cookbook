#ifndef VBOPLANE_H
#define VBOPLANE_H

#include "drawable.h"
#include <string>
#include "GLSLProgram.h"
using std::string;
class VBOPlane : public Drawable
{
private:
	GLSLProgram *mProgram;
    unsigned int vaoHandle;
    int faces;

public:
    VBOPlane(GLSLProgram *program, float xsize, float zsize, int xdivs, int zdivs, const string &vertexPos, const string &vertexNormal, const string &vertexTex, 
		float smax = 1.0f, float tmax = 1.0f);

    void render() const;
};

#endif // VBOPLANE_H
