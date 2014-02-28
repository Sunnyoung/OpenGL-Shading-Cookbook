in vec3 FrontColor;
in vec3 BackColor;
in vec2 TexCoord;
out vec4 FragColor;

void main(){
	//const float scale = 15.0;
	bvec2 isDiscard = greaterThan( fract(TexCoord * 15.0), vec2(0.2, 0.2));

	if(all(isDiscard))
		discard;
	else{
		if(gl_FrontFacing){
			FragColor = vec4(FrontColor, 1.0);
		} else {
			FragColor = vec4(BackColor, 1.0);
		}
	}
}