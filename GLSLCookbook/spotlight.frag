in vec4 Position;
in vec3 Normal;

struct SpotLight{
	vec4 position;
	vec3 intensity;
	vec3 direction;
	float exponent;//˥��ָ��
	float cutoff;//�۹�Ƶ�Բ׶��
};

uniform SpotLight spotlight;

uniform vec3 Ka;
uniform vec3 Kd;
uniform vec3 Ks;
uniform float Shininess;

uniform int IsSpot;
out vec4 FragColor;

//n �� position ����λ���Ӿ�����ϵ
vec3 spotAds(vec3 n, vec4 position){
	vec3 ambient = vec3(0.0);
	vec3 diffuse = vec3(0.0);
	vec3 specular = vec3(0.0);
	
	ambient = spotlight.intensity * Ka;

	vec3 s = normalize(vec3(spotlight.position - Position));
	vec3 norSporDir = normalize(spotlight.direction);
	float angle = acos(dot(-s, norSporDir));//�����;۹�Ʒ���ļн�
	float cutoff = radians(clamp(spotlight.cutoff, 0.0, 90.0));//���Բ׶�ǣ�������ת���ɻ���
	
	if(angle < cutoff){//ֻ������Ƕ�С��Բ׶�ǣ����ھ۹�Ƶķ�Χ֮��
		float factor = pow(dot(-s, norSporDir), spotlight.exponent);
		vec3 v = normalize(vec3(-Position));
		vec3 h = normalize(v + s);
		diffuse = factor * spotlight.intensity * Kd * max(dot(s, n), 0.0);
		specular = factor * spotlight.intensity * Ks * pow(max(dot(h, n), 0.0) ,Shininess);

		return ambient + diffuse + specular;
	} else {
		return ambient;
	}
} 

vec3 normalAds(vec3 n, vec4 position){

	vec3 s = normalize(vec3(spotlight.position - Position));
	vec3 r = normalize(reflect(-s, n));
	vec3 v = normalize(vec3(-position));

	return spotlight.intensity * (Ka + Kd * max(dot(s, n), 0.0) + Ks * pow(max(dot(r, v), 0.0), Shininess));
}


void main(){
	if(IsSpot != 0)
		FragColor = vec4(spotAds(Normal, Position), 1.0);
	else
		FragColor = vec4(normalAds(Normal, Position), 1.0);
}

//in vec3 Position;
//in vec3 Normal;
//
//struct SpotLightInfo {
//	vec4 position;   // Position in eye coords
//	vec3 intensity;
//	vec3 direction;  // Direction of the spotlight in eye coords.
//	float exponent;  // Angular attenuation exponent
//	float cutoff;    // Cutoff angle (between 0 and 90)
//};
//uniform SpotLightInfo spotlight;
//
//uniform vec3 Kd;            // Diffuse reflectivity
//uniform vec3 Ka;            // Ambient reflectivity
//uniform vec3 Ks;            // Specular reflectivity
//uniform float Shininess;    // Specular shininess factor
//
//out vec4 FragColor;
//
//vec3 adsWithSpotlight( )
//{
//	vec3 s = normalize( vec3( spotlight.position) - Position );
//	vec3 spotDir = normalize( spotlight.direction);
//	float angle = acos( dot(-s, spotDir) );
//	float cutoff = radians( clamp( spotlight.cutoff, 0.0, 90.0 ) );
//	vec3 ambient = spotlight.intensity * Ka;
//
//	if( angle < cutoff ) {
//		float spotFactor = pow( dot(-s, spotDir), spotlight.exponent );
//		vec3 v = normalize(vec3(-Position));
//		vec3 h = normalize( v + s );
//
//		return
//			ambient +
//			spotFactor * spotlight.intensity * (
//			Kd * max( dot(s, Normal), 0.0 ) +
//			Ks * pow( max( dot(h,Normal), 0.0 ), Shininess )
//			);
//	} else {
//		return ambient;
//	}
//}
//
//void main() {
//	FragColor = vec4(adsWithSpotlight(), 1.0);
//}
