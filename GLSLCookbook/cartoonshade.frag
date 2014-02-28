in vec3 Position;
in vec3 Normal;

uniform vec4 LightPosition;
uniform vec3 LightIntensity;

uniform vec3 Ka, Kd, Ks;

out vec4 FragColor;

const int levels = 3;

vec3 cartoonADS(vec3 n, vec3 position){
	float scale = 1.0 / levels;
	vec3 ambient = LightIntensity * Ka;
	vec3 s = normalize(vec3(LightPosition) - position);
	float cosine = max(dot(s, n), 0.0);
	vec3 diffuse = LightIntensity * Kd * floor(cosine * levels) * scale;

	return ambient + diffuse;
}

void main(){
	FragColor = vec4(cartoonADS(Normal, Position), 1.0);
}