#version 330 core

out vec4 FragColor;

in vec3 v_position;
in vec3 v_normal;
in vec2 v_uv;

// 光照配置
struct Light {
     vec3 color;
     vec3 position;
     float shininess;
};

// 相机配置
struct Camera {
     vec3 position;
};

uniform sampler2D texture_diffuse0;
uniform sampler2D texture_specular0;
uniform sampler2D texture_normal0;

uniform Light light;
uniform Camera camera;
// uniform Material material;


void main() {

     vec3 normal = -normalize(v_normal);
     vec3 lightDir = normalize(light.position - v_position);
     vec3 viewDir = normalize(camera.position - v_position);
     vec3 reflectDir = reflect(lightDir, normal);

     // 环境光
     vec3 ambientColor = texture(texture_diffuse0, vec2(v_uv.x, 1. - v_uv.y)).rgb * 0.3;

     vec3 diffuseColor = light.color * max(dot(normal, lightDir), 0.0) * texture(texture_diffuse0, vec2(v_uv.x, 1. - v_uv.y)).rgb;

     vec3 specularColor = pow(max(dot(viewDir, reflectDir), 0.0), 3.) * texture(texture_specular0, vec2(v_uv.x, 1. - v_uv.y)).rgb;


     FragColor = vec4(ambientColor + diffuseColor + specularColor, 1.0f);
//    FragColor = vec4(1.0f, 0.0f, 0.0f, 1.0);
}