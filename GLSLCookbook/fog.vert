in vec3 VertexPosition;
in vec3 VertexNormal;

uniform mat4 MV, MVP;
uniform mat3 NM;

out vec3 Position;
out vec3 Normal;

void main(){
	Position = vec3(MV * vec4(VertexPosition, 1.0));
	Normal = normalize(NM * VertexNormal);

	gl_Position = MVP * vec4(VertexPosition, 1.0);
}