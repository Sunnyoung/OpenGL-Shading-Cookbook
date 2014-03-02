in vec3 VertexPosition;
in vec3 VertexNormal;
in vec2 VertexTexCoord;

uniform vec4 LightPosition;

uniform vec3 La;
uniform vec3 Ld;
uniform vec3 Ls;

uniform vec3 Ka;
uniform vec3 Kd;
uniform vec3 Ks;

uniform float Shininess;

uniform mat3 NM;
uniform mat4 MV;
uniform mat4 MVP;

out vec3 FrontColor;
out vec3 BackColor;
out vec2 TexCoord;

void getEyeSpace(out vec3 norm, out vec4 position){
	norm = normalize(NM * VertexNormal);
	position = MV * vec4(VertexPosition, 1.0);
}

vec3 ads(vec3 n, vec4 position){
	vec3 s = normalize(vec3(LightPosition - position));
	vec3 r = reflect(-s, n);
	vec3 v = normalize(-position.xyz);

	vec3 ambient = La * Ka;
	vec3 diffuse = Ld * Kd * max(dot(s, n), 0.0);
	vec3 spec = vec3(0.0);
	if(dot(s, n) > 0){
		spec = Ls * Ks * pow(max(dot(r, v), 0.0), Shininess);
	}

	return ambient + diffuse + spec;
}

void main(){
	vec3 n;
	vec4 posInEye;
	getEyeSpace(n, posInEye);

	FrontColor = ads(n, posInEye);
	BackColor = ads(-n, posInEye);
	TexCoord = VertexTexCoord;

	gl_Position = MVP * vec4(VertexPosition, 1.0);
}