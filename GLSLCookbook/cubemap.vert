in vec3 VertexPosition;
in vec3 VertexNormal;
in vec2 VertexTexCoord;

out vec3 ReflectDir;

uniform mat4 M, MV, P, MVP;
uniform mat3 NM;
uniform vec3 WorldCameraPosition;
uniform bool DrawSkyBox;

void main(){
	//if(DrawSkyBox){
	//	ReflectDir = VertexPosition;
	//} else {
	//	vec3 worldPos = vec3(M * vec4(VertexPosition, 1.0));
	//	vec3 worldNorm = vec3(M * vec4(VertexNormal, 1.0));
	//	vec3 worldView = normalize(WorldCameraPosition - worldPos);

	//	ReflectDir = reflect(-worldView, worldNorm);
	//}

	if( DrawSkyBox ) {
		ReflectDir = VertexPosition;
	} else {
		vec3 worldPos = vec3( M * vec4(VertexPosition,1.0) );
		vec3 worldNorm = vec3(M * vec4(VertexNormal, 0.0));
		vec3 worldView = normalize( WorldCameraPosition - worldPos );

		ReflectDir = reflect(-worldView, worldNorm );
	}
	gl_Position = MVP * vec4(VertexPosition, 1.0);
}