in vec3 VertexPosition;
in vec3 VertexNormal;

uniform vec4 LightPosition;
uniform vec3 LightIntensity;
uniform float Shininess;

uniform vec3 Ka;
uniform vec3 Kd;
uniform vec3 Ks;


uniform mat4 MV;
uniform mat3 NM;
uniform mat4 MVP;

out vec4 Position;
out vec3 Normal;

out vec3 LightDir;
out vec3 ViewDir;
void main(){
	Position = MV * vec4(VertexPosition, 1.0);
	Normal = normalize(NM * VertexNormal);

	LightDir = normalize(vec3(LightPosition - Position));
	ViewDir = normalize(vec3(-Position));

	gl_Position = MVP * vec4(VertexPosition, 1.0);
}