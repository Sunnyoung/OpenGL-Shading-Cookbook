in vec3 VertexPosition;
in vec3 VertexNormal;
in vec2 VertexTexCoord;

out vec3 Position;
out vec3 Normal;
out vec2 TexCoord;

uniform mat4 MV; 
uniform mat4 MVP;
uniform mat3 NM;

void main(){
	Position = vec3(MV * vec4(VertexPosition, 1.0));
	Normal = normalize(NM * VertexNormal);
	TexCoord = VertexTexCoord;

	gl_Position = MVP * vec4(VertexPosition, 1.0);
}

