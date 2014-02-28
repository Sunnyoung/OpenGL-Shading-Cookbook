#pragma once
#include <GL/freeglut.h>
#include <string>
class ShaderUtil{
public:
	static GLuint createProgram(const std::string &vertexfile, const std::string &fragfile);
private:
	static GLuint createShader(GLenum shadertype, std::string filename);
};

