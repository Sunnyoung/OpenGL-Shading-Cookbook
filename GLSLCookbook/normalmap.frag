in vec3 LightDir;
in vec2 TexCoord;
in vec3 ViewDir;
in vec3 Normal;
out vec4 FragColor;

uniform sampler2D ColorTex;
uniform sampler2D NormalMapTex;

uniform vec4 LightPosition;
uniform vec3 LightIntensity;

uniform vec3 Ka, Ks;
uniform float Shininess;

vec3 ads(vec3 n, vec3 diffuseColor){
	vec3 ambient = LightIntensity * Ka;
	vec3 diffuse = LightIntensity * diffuseColor * max(dot(LightDir, n), 0.0);

	vec3 specular = vec3(0.0);
	if(dot(LightDir, n) > 0.0){
		vec3 r = normalize(reflect(-LightDir, n));
		specular = LightIntensity * Ks * pow(max(dot(r, ViewDir), 0.0), Shininess);
	}

	return ambient + diffuse + specular;
}

vec3 phongModel( vec3 norm, vec3 diffR ) {
	vec3 r = reflect( -LightDir, norm );
	vec3 ambient = LightIntensity * Ka;
	float sDotN = max( dot(LightDir, norm), 0.0 );
	vec3 diffuse = LightIntensity * diffR * sDotN;

	vec3 spec = vec3(0.0);
	if( sDotN > 0.0 )
		spec = LightIntensity * Ks *
		pow( max( dot(r,ViewDir), 0.0 ), Shininess );

	return ambient + diffuse + spec;
}

void main(){
	vec4 texColor = texture(ColorTex, TexCoord);
	vec4 normal = 2.0 * texture( NormalMapTex, TexCoord ) - 1.0;
	//vec4 normal = 2 * texture( NormalMapTex, TexCoord );
	//FragColor = vec4(ads(normal.xyz, texColor.rgb), 1.0);
	FragColor = vec4(ads(normal.xyz, normal.xyz), 1.0);
	//FragColor = vec4( phongModel(normal.xyz, texColor.rgb), 1.0 );
}