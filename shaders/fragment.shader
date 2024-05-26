#version 330 core

out vec4 color;

uniform vec4 u_frag_color;
uniform float u_Time;

void main() {
	 vec2 coord = gl_FragCoord.xy / vec2(640, 480);
	 float gradf = (coord.x * coord.y + u_frag_color.x + u_frag_color.y + u_frag_color.z)/4;
	 color = (vec4(sin(u_Time), gradf, 1.0 - gradf, 1.0)) / 2;
};