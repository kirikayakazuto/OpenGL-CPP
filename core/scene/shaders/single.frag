#version 330 core

out vec4 FragColor;

in vec3 v_position;
in vec3 v_normal;
in vec2 v_uv;

void main() {
    FragColor = vec4(0.5f, 0.5f, 0.5f, 1.0f);
}