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

void main(){
	Position = MV * vec4(VertexPosition, 1.0);
	Normal = normalize(NM * VertexNormal);

	gl_Position = MVP * vec4(VertexPosition, 1.0);
}