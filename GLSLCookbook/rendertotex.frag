in vec3 Position;
in vec3 Normal;
in vec2 TexCoord;

out vec4 FragColor;

uniform sampler2D RenderTex;

uniform vec4 LightPosition;
uniform vec3 LightIntensity;

uniform vec3 Ka, Kd, Ks;
uniform float Shininess;

vec3 phong(vec3 n, vec3 pos){
	//vec3 ambient = LightIntensity * Ka;
	//vec3 s = normalize(vec3(LightPosition) - pos);
	//float sDotn = dot(s, n);
	//vec3 diffuse = LightIntensity * Kd * max(sDotn, 0.0);
	//vec3 spec = vec3(0.0);
	//if(sDotn > 0.0){
	//	vec3 r = normalize(reflect(-s, n));
	//	vec3 v = normalize(-pos);
	//	spec = LightIntensity * Ks * pow(max(dot(r, v), 0.0), Shininess);
	//}
	//return ambient + diffuse + spec;

	vec3 s = normalize(vec3(LightPosition) - pos);
	vec3 v = normalize(-pos.xyz);
	vec3 r = reflect( -s, n );
	vec3 ambient = LightIntensity * Ka;
	float sDotN = max( dot(s,n), 0.0 );
	vec3 diffuse = LightIntensity * Kd * sDotN;
	vec3 spec = vec3(0.0);
	if( sDotN > 0.0 )
		spec = LightIntensity * Ks *
		pow( max( dot(r,v), 0.0 ), Shininess );

	return ambient + diffuse + spec;
}

void main(){
	vec4 color = texture(RenderTex, TexCoord);
	FragColor = vec4(phong(Normal, Position), 1.0) * color;
	//FragColor = vec4(1.0);
}