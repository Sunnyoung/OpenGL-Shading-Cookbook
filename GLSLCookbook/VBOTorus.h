#pragma once
#include "DEFINES.h"
#include "drawable.h"
#include <string>
#include "GLSLProgram.h"
class VBOTorus :
	public Drawable
{
public:
	VBOTorus(GLSLProgram *prog, float outerRadius, float innerRadius, int nsides, int nrings, const std::string &vertesPos, 
		const std::string &vertexNormal, const std::string &vertexTex0);
	virtual ~VBOTorus(void);
	virtual void render() const;
private:
	void generateVerts(float *verts, float *norms, float *tex, unsigned int *el, float outerRadius, float innerRadius);
private:
	GLuint mVAO;
	int mFaces, mRings, mSides;
	GLSLProgram *mProgram;
};

