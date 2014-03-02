in vec3 VertexPosition;
in vec3 VertexNormal;

out vec3 ReflectDir;
out vec3 RefractDir;

uniform float ReflectFactor, RefractFactor;

uniform mat4 M, MVP;
uniform vec3 WorldCameraPosition;
uniform bool DrawSkyBox;

void main(){
	if(DrawSkyBox){
		ReflectDir = VertexPosition;
	} else {
		vec3 worldPos = vec3(M * vec4(VertexPosition, 1.0));
		vec3 worldNorm = vec3(M * vec4(VertexNormal, 0.0));
		vec3 wordView = normalize(WorldCameraPosition - worldPos);
		ReflectDir = reflect(-wordView, worldNorm);
		RefractDir = refract(-wordView, worldNorm, RefractFactor);
	}

	gl_Position = MVP * vec4(VertexPosition, 1.0);

	//if( DrawSkyBox ) {
	//	ReflectDir = VertexPosition;
	//} else {
	//	vec3 worldPos = vec3( M * vec4(VertexPosition,1.0) );
	//	vec3 worldNorm = vec3(M * vec4(VertexNormal, 0.0));
	//	vec3 worldView = normalize( WorldCameraPosition - worldPos );

	//	ReflectDir = reflect(-worldView, worldNorm );
	//	RefractDir = refract(-worldView, worldNorm, RefractFactor );
	//}
	//gl_Position = MVP * vec4(VertexPosition,1.0);
}