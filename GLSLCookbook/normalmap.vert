in vec3 VertexPosition;
in vec3 VertexNormal;
in vec2 VertexTexCoord;
in vec4 VertexTangent;

out vec3 LightDir;
out vec2 TexCoord;
out vec3 ViewDir;
out vec3 Normal;

uniform vec4 LightPosition;
uniform vec4 LightIntensity;

uniform mat4 MV, MVP;
uniform mat3 NM;

void main(){
	vec3 norm = normalize(NM * VertexNormal);
	Normal = norm;
	vec3 tang = normalize(NM * vec3(VertexTangent));
	vec3 binorm = normalize(cross(norm, tang)) * VertexTangent.w;

	mat3 toObjectLocal = mat3(
		tang.x, binorm.x, norm.x,
		tang.y, binorm.y, norm.y,
		tang.z, binorm.z, norm.z);

	vec3 position = vec3(MV * vec4(VertexPosition, 1.0));
	LightDir = normalize(toObjectLocal*(vec3(LightPosition) - position));
	TexCoord = VertexTexCoord;
	ViewDir = toObjectLocal * normalize(-position);

	gl_Position = MVP * vec4(VertexPosition, 1.0);


}