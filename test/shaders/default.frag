#version 330 core

out vec4 FragColor;

in vec3 v_position;
in vec3 v_normal;
in vec3 v_color;
in vec2 v_uv;

uniform sampler2D mainTexture;

void main() {
    FragColor = texture(mainTexture, v_uv);
}