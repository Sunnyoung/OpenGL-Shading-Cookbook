#ifndef SKYBOX_H
#define SKYBOX_H
#include "DEFINES.h"
#include "drawable.h"
#include <string>
using std::string;
class SkyBox : public Drawable{
private:
    unsigned int vaoHandle;

public:
    SkyBox(GLuint program, const string &vertexPos);

    void render() const;
};


#endif // SKYBOX_H
