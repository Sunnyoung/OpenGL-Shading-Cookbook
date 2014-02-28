in vec3 Position;
in vec3 Normal;
in vec2 TexCoord;

out vec4 FragColor;

uniform vec4 LightPosition;
uniform vec3 LightIntensity;

uniform vec3 Ka, Kd, Ks;
uniform float Shininess;

uniform sampler2D BaseTex;
uniform sampler2D AlphaTex;

vec3 ads(vec3 n, vec3 position, out vec3 ambient, out vec3 diffuse, out vec3 spec){
	ambient = LightIntensity * Ka;
	vec3 s = normalize(vec3(LightPosition) - position);
	diffuse = LightIntensity * Kd * max(dot(s, n), 0.0);
	vec3 v = normalize(-position);
	vec3 h = normalize(s + v);
	spec = LightIntensity * Ks * pow(max(dot(h, n), 0.0), Shininess);

	return ambient + diffuse + spec;
}

void main(){
	vec3 ambient, diffuse, spec;
	ads(Normal, Position, ambient, diffuse, spec);
	
	vec4 baseTexColor = texture(BaseTex, TexCoord);
	vec4 alphaTexColor = texture(AlphaTex, TexCoord);

	if(alphaTexColor.a < 0.15)
		discard;
	else {
		if(gl_FrontFacing)
			FragColor = vec4(ads(Normal, Position, ambient, diffuse, spec), 1.0) * baseTexColor;
		else
			FragColor = vec4(ads(-Normal, Position, ambient, diffuse, spec), 1.0) * baseTexColor;
	}
}