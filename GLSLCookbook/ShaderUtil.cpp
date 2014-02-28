#include "ShaderUtil.h"
#include <fstream>
#include <sstream>
using namespace std;

GLuint ShaderUtil::createProgram(const std::string &vertexfile, const std::string &fragfile ){
	GLuint vertexShader = createShader(GL_VERTEX_SHADER, vertexfile);
	GLuint fragShader = createShader(GL_FRAGMENT_SHADER, fragfile);

	GLuint program = glCreateProgram();
	if(0 == program) {
		fprintf(stderr, "Error creating program object.\n");
		exit(1);
	}

	// Bind index 0 to the shader input variable "VertexPosition"
	//glBindAttribLocation(programHandle, 0, "VertexPosition");
	// Bind index 1 to the shader input variable "VertexColor"
	//glBindAttribLocation(programHandle, 1, "VertexColor");

	// Attach the shaders to the program object
	glAttachShader( program, vertexShader );
	glAttachShader( program, fragShader );

	// Link the program
	glLinkProgram( program );

	// Check for successful linking
	GLint status;
	glGetProgramiv( program, GL_LINK_STATUS, &status );
	if (GL_FALSE == status) {

		fprintf( stderr, "Failed to link shader program!\n" );

		GLint logLen;
		glGetProgramiv( program, GL_INFO_LOG_LENGTH, &logLen );

		if (logLen > 0) {
			char * log = (char *)malloc(logLen);
			GLsizei written;
			glGetProgramInfoLog(program, logLen, &written, log);
			fprintf(stderr, "Program log: \n%s", log);
			free(log);
		}
		glDeleteProgram(program);
	}
	return program;
}

GLuint ShaderUtil::createShader( GLenum shadertype, std::string filename ){
	ifstream inFile( filename );
	if (!inFile) {
		fprintf(stderr, "Error opening file : %s \n", filename.c_str() );
		exit(1);
	}

	std::stringstream code;
	code << inFile.rdbuf();
	inFile.close();
	string codeStr(code.str());

	GLuint shader = glCreateShader( shadertype );
	if (0 == shader) {
		fprintf(stderr, "Error creating vertex shader.\n");
		exit(EXIT_FAILURE);
	}

	// Load the source code into the shader object
	const GLchar* codeArray[] = {codeStr.c_str()};
	glShaderSource(shader, 1, codeArray, NULL);

	// Compile the shader
	glCompileShader( shader );

	// Check compilation status
	GLint result;
	glGetShaderiv( shader, GL_COMPILE_STATUS, &result );
	if( GL_FALSE == result ) {
		string type;
		GL_VERTEX_SHADER == shadertype ? type = "Vertex Shader" : type = "Fragment Shader";
		fprintf( stderr, "%s compilation failed!\n", type.c_str());

		GLint logLen;
		glGetShaderiv( shader, GL_INFO_LOG_LENGTH, &logLen );
		if (logLen > 0) {
			char * log = (char *)malloc(logLen);
			GLsizei written;
			glGetShaderInfoLog(shader, logLen, &written, log);
			fprintf(stderr, "Shader log: \n%s", log);
			free(log);
		}
		glDeleteShader(shader);
	}

	return shader;
}
