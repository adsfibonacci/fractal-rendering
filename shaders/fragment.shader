#version 330 core

layout(location=0) out vec4 color;

uniform vec4 u_Color;
uniform float u_Time;

void main() {
	 vec2 coord = gl_FragCoord.xy / vec2(640, 480);
	 float gradf = (coord.x * coord.y + u_Color.x + u_Color.y + u_Color.z)/4;	 
	 color = vec4(sin(u_Time), gradf, 1.0 - gradf, 1.0);
};