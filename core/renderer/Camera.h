//
// Created by 邓朗 on 2024/1/6.
//

#ifndef LEARN_OPENGL_CAMERA_H
#define LEARN_OPENGL_CAMERA_H

//#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>

class Camera {
public:
    //
    glm::vec3 position;
    glm::vec3 toward;
    glm::vec3 up;

    glm::mat4 matrix;

    unsigned int width;
    unsigned int height;

    Camera(int width, int height, glm::vec3 position);

    void UpdateMatrix(float FOVdeg, float nearPlane, float farPlane);

    void OnInput(GLFWwindow* window);
};


#endif //LEARN_OPENGL_CAMERA_H
