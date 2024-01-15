#version 330 core

layout (location = 0) in vec3 a_position;
layout (location = 1) in vec3 a_color;
layout (location = 2) in vec2 a_uv;

// 差值数据
out vec3 v_position;
out vec3 v_color;
out vec2 v_uv;

// uniform
uniform mat4 u_cameraMatrix;

//
void main() {
	v_position = a_position;
	v_color = a_color;
	v_uv = a_uv;

	// Outputs the positions/coordinates of all vertices
	gl_Position = u_cameraMatrix * vec4(v_position, 1.0);
	// gl_Position = vec4(v_position, 1.0);
}