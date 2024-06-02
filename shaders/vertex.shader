#version 330 core

layout(location=0) in vec4 position;

struct camera {
	   mat4 model;
	   mat4 view;
	   mat4 proj;
};

uniform mat4 u_view;

void main() {
	 gl_Position = u_view * position;
};