#version 330 core

struct Material {
	   vec3 col;
};
struct Light {
	   vec3 col;
};

out vec4 color;

uniform Material u_bronze;
uniform Light u_orange;

uniform float u_Time;

void main() {		
	 vec2 coord = gl_FragCoord.xy / vec2(500, 500);
	 float gradf = coord.x * coord.y;
	 color = (vec4(sin(u_Time), gradf, 1.0 - gradf, 1.0)) / 2;
	 color = (color + vec4(u_bronze.col + u_orange.col, 1.0)) / 3;
};