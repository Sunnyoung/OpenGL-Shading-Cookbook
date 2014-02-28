in vec3 Position;
in vec3 Normal;
in vec2 TexCoord;

out vec4 FragColor;

uniform sampler2D Tex1;
uniform sampler2D Tex2;

uniform vec4 LightPosition;
uniform vec3 LightIntensity;

uniform vec3 Ka, Kd, Ks;
uniform float Shininess;


vec3 ads(vec3 n, vec3 position, out vec3 ambient, out vec3 diffuse, out vec3 specular){
	ambient = LightIntensity * Ka;
	vec3 s = normalize(vec3(LightPosition) - position);
	diffuse = LightIntensity * Kd * max(dot(s, n), 0.0);
	
	vec3 v = normalize(-position);
	vec3 h = normalize(s + v);

	specular =  LightIntensity * Ks * pow(max( 0.0, dot( h, n)), Shininess);

	return ambient + diffuse + specular;
}


void main(){
	vec3 ambient = vec3(1.0);
	vec3 diffuse = vec3(1.0);
	vec3 spec = vec3(1.0);
	ads(Normal, Position, ambient, diffuse, spec);
	vec4 texColor1 = texture(Tex1, TexCoord);
	vec4 texColor2 = texture(Tex2, TexCoord);
	vec4 texColor = mix(texColor1, texColor2, texColor2.a);//texColor1 * (1 - texColor2.a) + texColor2 * texColor2.a
	//vec4 texColor = texColor1 * (1 - texColor1.a) + texColor2 * texColor1.a;
	//FragColor = vec4(ambient + diffuse, 1.0) * texColor + vec4(spec, 1.0);
	//if(texColor2.a < 0.15)
	//	discard;
	//else {
	//	if(gl_FrontFacing)
	//		FragColor = vec4(ads(Normal, Position, ambient, diffuse, spec), 1.0) * texColor1;
	//	else
	//		FragColor = vec4(ads(-Normal, Position, ambient, diffuse, spec), 1.0) * texColor1;
	//}
	FragColor = vec4(ads(Normal, Position, ambient, diffuse, spec), 1.0);
}