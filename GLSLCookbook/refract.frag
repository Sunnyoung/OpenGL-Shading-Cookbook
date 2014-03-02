in vec3 ReflectDir;
in vec3 RefractDir;

out vec4 FragColor;

uniform samplerCube CubeMapTex;
uniform bool DrawSkyBox;

uniform float ReflectFactor, RefractFactor;

void main(){
	vec4 reflectColor = texture(CubeMapTex, ReflectDir);
	vec4 refractColor = texture(CubeMapTex, RefractDir);

	if(DrawSkyBox)
		FragColor = reflectColor;
	else 
		FragColor = mix(refractColor, reflectColor, ReflectFactor);
	//vec4 reflectColor = texture(CubeMapTex, ReflectDir);
	//vec4 refractColor = texture(CubeMapTex, RefractDir);

	//if( DrawSkyBox )
	//	FragColor = reflectColor;
	//else
	//	FragColor = mix(refractColor, reflectColor, ReflectFactor);
}