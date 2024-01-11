//
// Created by 邓朗 on 2024/1/6.
//

#ifndef LEARN_OPENGL_CAMERA_H
#define LEARN_OPENGL_CAMERA_H

//#include<glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>
#include "Renderer.h"

class Camera {
public:
    //
    glm::vec3 position;
    glm::vec3 toward;
    glm::vec3 up;

    glm::mat4 view;

    glm::mat4 projection;

    glm::mat4 matrix;

    unsigned int width;
    unsigned int height;

    // 视角
    float fov;
    // 近平面
    float nearPlane;
    // 远平面
    float farPlane;



    Camera(int width, int height, glm::vec3 position, float fov, float near, float far);

    void UpdateMatrix();

    void OnInput();
};


#endif //LEARN_OPENGL_CAMERA_H
