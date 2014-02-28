#include "VBOTorus.h"
#include "cmath"
#include "DEFINES.h"

VBOTorus::VBOTorus(GLSLProgram *prog, float outerRadius, float innerRadius, int nsides, int nrings, const std::string &vertesPos, 
				   const std::string &vertexNormal, const std::string &vertexTex0) : mSides(nsides), mRings(nrings){
	mProgram = prog;
	
	mFaces = mSides * mRings;
	int nVerts  = mSides * (mRings+1);   // One extra ring to duplicate first ring

	// Verts
	float * v = new float[3 * nVerts];
	// Normals
	float * n = new float[3 * nVerts];
	// Tex coords
	float * tex = new float[2 * nVerts];
	// Elements
	unsigned int * el = new unsigned int[6 * mFaces];

	// Generate the vertex data
	generateVerts(v, n, tex, el, outerRadius, innerRadius);

	// Create and populate the buffer objects
	unsigned int handle[4];
	glGenBuffers(4, handle);

	glBindBuffer(GL_ARRAY_BUFFER, handle[0]);
	glBufferData(GL_ARRAY_BUFFER, (3 * nVerts) * sizeof(float), v, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, handle[1]);
	glBufferData(GL_ARRAY_BUFFER, (3 * nVerts) * sizeof(float), n, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, handle[2]);
	glBufferData(GL_ARRAY_BUFFER, (2 * nVerts) * sizeof(float), tex, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, handle[3]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * mFaces * sizeof(unsigned int), el, GL_STATIC_DRAW);

	delete [] v;
	delete [] n;
	delete [] el;
	delete [] tex;

	// Create the VAO
	glGenVertexArrays( 1, &mVAO );
	glBindVertexArray(mVAO);

	int progHandle = mProgram->getProgram();

	int posLoc = glGetAttribLocation(progHandle, vertesPos.c_str());
	glEnableVertexAttribArray(posLoc);  // Vertex position
	glBindBuffer(GL_ARRAY_BUFFER, handle[0]);
	glVertexAttribPointer(posLoc, 3, GL_FLOAT, GL_FALSE, 0, ((GLubyte *)NULL + (0)) );

	int norLoc = glGetAttribLocation(progHandle, vertexNormal.c_str());
	glEnableVertexAttribArray(norLoc);  // Vertex normal
	glBindBuffer(GL_ARRAY_BUFFER, handle[1]);
	glVertexAttribPointer( norLoc, 3, GL_FLOAT, GL_FALSE, 0, ((GLubyte *)NULL + (0)) );

	int tex0Loc = glGetAttribLocation(progHandle, vertexTex0.c_str());
	glBindBuffer(GL_ARRAY_BUFFER, handle[2]);
	glEnableVertexAttribArray(tex0Loc);  // Texture coords
	glVertexAttribPointer( tex0Loc, 2, GL_FLOAT, GL_FALSE, 0, ((GLubyte *)NULL + (0)) );

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, handle[3]);

	glBindVertexArray(0);
}

VBOTorus::~VBOTorus(void){
}

void VBOTorus::render() const{
	glBindVertexArray(mVAO);
	glDrawElements(GL_TRIANGLES, 6 * mFaces, GL_UNSIGNED_INT, ((GLubyte *)NULL + (0)));
}

void VBOTorus::generateVerts( float *verts, float *norms, float *tex, unsigned int *el, float outerRadius, float innerRadius ){
	float ringFactor  = (float)(TWOPI / mRings);
	float sideFactor = (float)(TWOPI / mSides);
	int idx = 0, tidx = 0;
	for( int ring = 0; ring <= mRings; ring++ ) {
		float u = ring * ringFactor;
		float cu = cos(u);
		float su = sin(u);
		for( int side = 0; side < mSides; side++ ) {
			float v = side * sideFactor;
			float cv = cos(v);
			float sv = sin(v);
			float r = (outerRadius + innerRadius * cv);
			verts[idx] = r * cu;
			verts[idx + 1] = r * su;
			verts[idx + 2] = innerRadius * sv;
			norms[idx] = cv * cu * r;
			norms[idx + 1] = cv * su * r;
			norms[idx + 2] = sv * r;
			tex[tidx] = (float)(u / TWOPI);
			tex[tidx+1] = (float)(v / TWOPI);
			tidx += 2;
			// Normalize
			float len = sqrt( norms[idx] * norms[idx] +
				norms[idx+1] * norms[idx+1] +
				norms[idx+2] * norms[idx+2] );
			norms[idx] /= len;
			norms[idx+1] /= len;
			norms[idx+2] /= len;
			idx += 3;
		}
	}

	idx = 0;
	for( int ring = 0; ring < mRings; ring++ ) {
		int ringStart = ring * mSides;
		int nextRingStart = (ring + 1) * mSides;
		for( int side = 0; side < mSides; side++ ) {
			int nextSide = (side+1) % mSides;
			// The quad
			el[idx] = (ringStart + side);
			el[idx+1] = (nextRingStart + side);
			el[idx+2] = (nextRingStart + nextSide);
			el[idx+3] = ringStart + side;
			el[idx+4] = nextRingStart + nextSide;
			el[idx+5] = (ringStart + nextSide);
			idx += 6;
		}
	}
}
