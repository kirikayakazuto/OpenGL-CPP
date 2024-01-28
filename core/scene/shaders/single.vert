#version 330 core

layout (location = 0) in vec3 a_position;
layout (location = 1) in vec3 a_normal;
layout (location = 2) in vec2 a_uv;
layout (location = 3) in vec3 a_tangent;
layout (location = 4) in vec3 a_bitangent;

// 差值数据
out vec3 v_position;
out vec3 v_normal;
out vec2 v_uv;

// uniform
uniform mat4 u_cameraMatrix;
uniform mat4 u_worldMatrix;

//
void main() {
    v_position = a_position;
    v_normal = a_normal;
    v_uv = a_uv;

    gl_Position = u_cameraMatrix * u_worldMatrix * vec4(v_position, 1.0);
}