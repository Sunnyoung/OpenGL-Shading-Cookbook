in vec4 Position;
in vec3 Normal;

uniform vec4 LightPosition;
uniform vec3 LightIntensity;
uniform float Shininess;

uniform vec3 Ka;
uniform vec3 Kd;
uniform vec3 Ks;

uniform int Halfway;

out vec4 FragColor;

vec3 ads(vec3 n, vec4 position){
	vec3 s= vec3(0.0);
	if(LightPosition.w == 0.0)
		s = normalize(vec3(LightPosition));
	else
		s = normalize(vec3(LightPosition - position));

	if(Halfway != 0){
		vec3 v = normalize(vec3(-position));
		vec3 h = normalize(s + v);

		return LightIntensity * (Ka + Kd * max(dot(s, n), 0.0) + Ks * pow(max(dot(h, n), 0.0), Shininess));
	} else {
		vec3 r = normalize(reflect(-s, n));
		vec3 v = normalize(vec3(-position));

		return LightIntensity * (Ka + Kd * max(dot(s, n), 0.0) + Ks * pow(max(dot(r, v), 0.0), Shininess));
	}
}

void main(){
	FragColor = vec4(ads(Normal, Position), 1.0);
}