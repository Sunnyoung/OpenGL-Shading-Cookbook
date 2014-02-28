in vec3 Position;
in vec3 Normal;

struct Fog{
	float maxDist;
	float minDist;
	vec3 color;
};

uniform Fog fog;

struct Light{
	vec4 position;
	vec3 intensity;
};

uniform Light light;

uniform vec3 Ka, Kd, Ks;
uniform float Shininess;

//vec3 ads(vec3 n, vec3 position){
//	vec3 ambient = light.intensity * Ka;
//	
//	vec3 s = normalize(vec3(light.position) - position);
//	vec3 v = normalize(-position);
//	vec3 h = normalize(s + v);
//	vec3 diffuse = light.intensity * Kd * max(dot(s, n), 0.0);
//	vec3 specular = light.intensity * Ks * pow(max(dot(h, n), 0.0), Shininess);
//
//	return  ambient + diffuse + specular;
//}

vec3 ads(){
	vec3 s = normalize( light.position.xyz - Position.xyz );
	vec3 v = normalize(vec3(-Position));
	vec3 h = normalize( v + s );

	vec3 ambient = Ka;
	vec3 diffuse = Kd * max(0.0, dot(s, Normal) );
	vec3 spec = Ks * pow( max( 0.0, dot( h, Normal) ), Shininess );

	return light.intensity * (ambient + diffuse + spec);
}

out vec4 FragColor;
void main(){
	float dist = abs(Position.z);
	float fogFactor = (fog.maxDist - dist) / (fog.maxDist - fog.minDist);
	fogFactor = clamp(fogFactor, 0.0, 1.0);
	vec3 adsColor = ads();
	vec3 color = mix(adsColor, fog.color, fogFactor);

	FragColor = vec4(color, 1.0);
}