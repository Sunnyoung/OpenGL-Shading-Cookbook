in vec3 VertexPosition;
in vec3 VertexNormal;

uniform vec4 LightPosition;
uniform vec3 LightIntensity;
uniform float Shininess;

uniform vec3 Ka;
uniform vec3 Kd;
uniform vec3 Ks;


uniform mat4 MV;
uniform mat3 NM;
uniform mat4 MVP;

out vec3 Color;

void getEyeSpace(out vec3 normal, out vec4 position){
	normal = normalize(NM * VertexNormal);
	position = MV * vec4(VertexPosition, 1.0);
}

vec3 ads(vec3 n, vec4 position){
	vec3 s= vec3(0.0);
	if(LightPosition.w == 0.0)
		s = normalize(vec3(LightPosition));
	else
		s = normalize(vec3(LightPosition - position));
	vec3 r = normalize(reflect(-s, n));
	vec3 v = normalize(vec3(-position));

	return LightIntensity * (Ka + Kd * max(dot(s, n), 0.0) + Ks * pow(max(dot(r, v), 0.0), Shininess));
}

void main(){
	vec3 normal;
	vec4 posInEye;
	getEyeSpace(normal, posInEye);
	Color = ads(normal, posInEye);

	gl_Position = MVP * vec4(VertexPosition, 1.0);
}

