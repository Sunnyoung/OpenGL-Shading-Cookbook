#ifndef VBOMESH_H
#define VBOMESH_H

#include "drawable.h"
#include <vector>
#include <glm/glm.hpp>
#include "DEFINES.h"
#include <string>
#include "GLSLProgram.h"
class VBOMesh : public Drawable
{
private:
	GLSLProgram *mProgram;
    unsigned int faces;
    unsigned int vaoHandle;

    bool reCenterMesh, loadTex, genTang;

    void trimString(std::string & str);
    
	void storeVBO( const std::vector<glm::vec3> &points, const std::string &vertexPos, 
		const std::vector<glm::vec3> & normals, const std::string &vertexNormal, 
		const std::vector<glm::vec2> &texCoords, const std::string &vertexTexcoords,
		const std::vector<glm::vec4> &tangents, const std::string &vertexTangents,
		const std::vector<int> &elements, const std::string &vertexEle);
    
	void generateAveragedNormals(const std::vector<glm::vec3> & points, std::vector<glm::vec3> & normals,
            const std::vector<int> & faces );
    
	void generateTangents(
            const std::vector<glm::vec3> & points, const std::vector<glm::vec3> & normals, 
			const std::vector<int> & faces, const std::vector<glm::vec2> & texCoords, 
			std::vector<glm::vec4> & tangents);
    
	void center(std::vector<glm::vec3> &);

public:
    VBOMesh(GLSLProgram *program, const std::string &fileName, const std::string &vertexPos, 
		const std::string &vertexNormal, const std::string &vertexTexcoords, const std::string &vertexTangents,
		const std::string &vertexEle, bool centre = false, bool loadTc = false, bool genTangents = false );

    void render() const;

	void loadOBJ(const std::string &fileName,  const std::string &vertexPos, const std::string &vertexNormal, 
		const std::string &vertexTexcoords, const std::string &vertexTangents, const std::string &vertexEle);
};

#endif // VBOMESH_H
