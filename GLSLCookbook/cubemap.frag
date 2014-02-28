in vec3 ReflectDir;

out vec4 FragColor;

uniform samplerCube CubeMapTex;
uniform bool DrawSkyBox;
uniform float ReflectFactor;
uniform vec4 MaterialColor;

void main(){
	//vec4 cubemapColor = texture(CubeMapTex, ReflectDir);
	//if(DrawSkyBox){
	//	FragColor = cubemapColor;
	//}else {
	//	FragColor = mix(MaterialColor, cubemapColor, ReflectFactor);
	//}
	vec4 cubeMapColor = texture(CubeMapTex, ReflectDir);

	if( DrawSkyBox )
		FragColor = cubeMapColor;
	else
		FragColor = mix( MaterialColor, cubeMapColor, ReflectFactor);
}