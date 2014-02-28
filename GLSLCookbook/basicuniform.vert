#version 400
//layout (location=0) in vec3 VertexPosition;
//layout (location=1) in vec3 VertexColor;
in vec3 VertexPosition;
in vec3 VertexColor;

uniform mat4 mvp;

varying vec3 Color;
void main(){
	Color = VertexColor;
	gl_Position = mvp * vec4(VertexPosition, 1.0);
}