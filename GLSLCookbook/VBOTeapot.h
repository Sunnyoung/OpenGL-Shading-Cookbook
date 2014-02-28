#pragma once
#include "Drawable.h"
#include <glm/glm.hpp>
#include "DEFINES.h"
#include "TeapotData.h"
#include <string>
#include "GLSLProgram.h"

class VBOTeapot : public Drawable{
public:
	VBOTeapot(GLSLProgram *program, int grid, glm::mat4 lidTransform, const std::string &vertexPos, const std::string &vertexNormal, 
		const std::string &vertexTex0);
	~VBOTeapot(void);
	void render() const;
private:
	 void generatePatches(float * v, float * n, float *tc, unsigned int* el, int grid);
	 void computeBasisFunctions( float * B, float * dB, int grid );
	 void buildPatch(glm::vec3 patch[][4], float *B, float *dB, float *v, float *n,float *tc, unsigned int *el, int &index, 
		 int &elIndex, int &tcIndex, int grid, glm::mat3 reflect, bool invertNormal);
	 void buildPatchReflect(int patchNum, float *B, float *dB, float *v, float *n, float *tc, unsigned int *el, 
		 int &index, int &elIndex, int &tcIndex, int grid, bool reflectX, bool reflectY);
	 void getPatch( int patchNum, glm::vec3 patch[][4], bool reverseV );
	 glm::vec3 evaluate( int gridU, int gridV, float *B, glm::vec3 patch[][4] );
	 glm::vec3 evaluateNormal( int gridU, int gridV, float *B, float *dB, glm::vec3 patch[][4] );
	 void moveLid(int grid, float *v, glm::mat4 lidTransform);
private:
	GLSLProgram *mProgram;
	GLuint vaoHandle;
	GLuint faces;
};

