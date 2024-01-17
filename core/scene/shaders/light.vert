#version 330 core

layout (location = 0) in vec3 a_position;
layout (location = 1) in vec3 a_color;

// 差值数据
out vec3 v_position;
out vec3 v_color;

// uniform
uniform mat4 u_cameraMatrix;
uniform mat4 u_worldMatrix;

//
void main() {
    v_position = a_position;
    v_color = a_color;

    gl_Position = u_cameraMatrix * u_worldMatrix * vec4(v_position, 1.0);
}