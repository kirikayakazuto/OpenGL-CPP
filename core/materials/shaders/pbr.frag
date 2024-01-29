#version 330 core

out vec4 FragColor;

in vec3 v_position;
in vec3 v_normal;
in vec2 v_uv;

uniform sampler2D texture_diffuse0;
uniform sampler2D texture_specular0;
uniform sampler2D texture_normal0;

void main() {
     FragColor = vec4(texture(texture_diffuse0, vec2(v_uv.x, 1. - v_uv.y)).rgb, 1.0f);
//    FragColor = vec4(1.0f, 0.0f, 0.0f, 1.0);
}