in vec3 VertexPosition;
in vec3 VertexNormal;

out vec3 EyePosition;
out vec3 EyeNormal;
out vec4 ProjTexCoord;

uniform mat4 M, MV, P, MVP;
uniform mat3 NM;
uniform mat4 ProjectorMatrix;


void main(){
	vec4 pos4 = vec4(VertexPosition, 1.0);

	EyePosition = vec3(MV * pos4);
	EyeNormal = normalize(NM * VertexNormal);
	ProjTexCoord = ProjectorMatrix * (M * pos4);

	gl_Position = MVP * pos4;
}