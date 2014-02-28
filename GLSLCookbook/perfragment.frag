in vec4 Position;
in vec3 Normal;

in vec3 LightDir;
in vec3 ViewDir;

uniform vec4 LightPosition;
uniform vec3 LightIntensity;
uniform float Shininess;

uniform vec3 Ka;
uniform vec3 Kd;
uniform vec3 Ks;

out vec4 FragColor;

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

//根据NormalMap模型的着色方法，顶点端传入的是光源向量(LightDir)和观察者向量(ViewDir)，而不是在片元端计算，这样计算的次数变少？
vec3 ads2(){
	vec3 ambient = LightIntensity * Ka;
	vec3 diffuse = LightIntensity * Kd * max(dot(LightDir, Normal), 0.0);

	vec3 specular = vec3(0.0);
	if(dot(LightDir, Normal) > 0.0){
		vec3 r = normalize(reflect(-LightDir, Normal));
		specular = LightIntensity * Ks * pow(max(dot(r, ViewDir), 0.0), Shininess);
	}

	return ambient + diffuse + specular;
}
void main(){
	FragColor = vec4(ads(Normal, Position), 1.0);
	//FragColor = vec4(ads2(), 1.0);
}