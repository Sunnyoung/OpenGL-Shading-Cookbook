in vec3 EyePosition;
in vec3 EyeNormal;
in vec4 ProjTexCoord;

out vec4 FragColor;

uniform vec4 LightPosition;
uniform vec3 LightIntensity;

uniform vec3 Ka, Kd, Ks;
uniform float Shininess;

uniform sampler2D ProjectorTex;

vec3 phong(vec3 n, vec3 pos){
	vec3 s = normalize(vec3(LightPosition) - pos);
	vec3 v = normalize(-pos);
	vec3 r = normalize(reflect(-s, n));
	
	vec3 ambient = LightIntensity * Ka;
	float sDotn = max(dot(s, n), 0.0);
	vec3 diffuse = LightIntensity * Kd * sDotn;
	vec3 spec = vec3(0.0);
	if(sDotn > 0.0){
		spec = LightIntensity * Ks * pow(max(dot(r, v), 0.0), Shininess);
	}

	return ambient + diffuse + spec;
}

void main(){
	vec3 color = phong(EyeNormal, EyePosition);

	vec4 projTexColor = vec4(0.0);
	if(ProjTexCoord.z > 0)
		projTexColor = textureProj(ProjectorTex, ProjTexCoord);

	FragColor = vec4(color, 1.0) + projTexColor;
}

