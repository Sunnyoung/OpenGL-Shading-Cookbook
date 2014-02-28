#pragma once
#include "DEFINES.h"
#include <string>
#include <glm/glm.hpp>

class GLSLProgram{
public:
	GLSLProgram(const std::string &vertexfile, const std::string &fragfile);
	~GLSLProgram(void);
	void setUniform(const std::string &name, const glm::mat4 &mat);
	void setUniform(const std::string &name, const glm::mat3 &mat);
	void setUniform(const std::string &name, const glm::vec4 &vec);
	void setUniform(const std::string &name, float x, float y, float z, float w);
	void setUniform(const std::string &name, const glm::vec3 &vec);
	void setUniform(const std::string &name, float x, float y, float z);
	void setUniform(const std::string &name, float value);
	void setUniform(const std::string &name, int value);
	void use();

	//test
	GLuint getProgram() const{ return mProgram; }
	bool isDebug() const { return mIsDebug; }
	void setDebug(bool val) { mIsDebug = val; }
private:
	GLuint createShader(GLenum shadertype, std::string filename);
	GLuint createProgram(const std::string &vertexfile, const std::string &fragfile );
	void checkLocation(const std::string &name, int location);
private:
	GLuint mProgram;
	bool mIsDebug;
};

