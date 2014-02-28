in vec3 VertexPosition;
in vec3 VertexNormal;

struct LightInfo {
  vec4 Position;  // Light position in eye coords.
  vec3 Intensity; // Light intesity (amb., diff., and spec.)
};
uniform LightInfo lights[5];

uniform mat4 MV;
uniform mat4 MVP;
uniform mat3 NM;

uniform vec3 Ka;
uniform vec3 Kd;
uniform vec3 Ks;
uniform float Shininess;

out vec3 Color;

void getEyeSpace(out vec3 n, out vec4 posInEye){
	n = normalize(NM * VertexNormal);
	posInEye = MV * vec4(VertexPosition, 1.0);
}

vec3 ads(int lightIndex, vec4 posInEye, vec3 n){
	vec3 amibent= lights[lightIndex].Intensity * Ka;
	
	vec3 s = normalize(vec3(lights[lightIndex].Position - posInEye));
	vec3 r = normalize(reflect(-s, n));
	vec3 diffuse = lights[lightIndex].Intensity * Kd * max(dot(s, n), 0.0);

	vec3 spec = vec3(0.0);
	vec3 v = normalize(vec3(-posInEye));
	if(dot(s, n) > 0){
		spec = lights[lightIndex].Intensity * Ks * pow(max(dot(r, v), 0.0), Shininess);
	}

	return amibent + diffuse + spec;
}

void main(){
	vec3 n;
	vec4 posInEye;
	getEyeSpace(n, posInEye);
	//vec3 n = normalize( NM * VertexNormal);
	//vec4 posInEye = MV * vec4(VertexPosition,1.0);

	Color = vec3(0.0);

	for( int i = 0; i < 6; i++ )
		Color += ads( i, posInEye, n );

	gl_Position = MVP * vec4(VertexPosition, 1.0);
}