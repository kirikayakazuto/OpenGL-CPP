cmake_minimum_required(VERSION 3.24)
project(learn_opengl)

find_package(OpenGL REQUIRED)

set(CMAKE_CXX_STANDARD 17)

# Including GLFW
add_subdirectory(libs/glfw)
include_directories(libs/glfw/include)

# Including GLAD
include_directories(libs/glad/include)

find_package(glm CONFIG REQUIRED)

set(SOURCE_FILES main.cpp libs/glad/src/glad.c core/renderer/Renderer.cpp core/renderer/Renderer.h core/scene/Scene.cpp core/scene/Scene.h core/scene/Node.cpp core/scene/Node.h core/scene/Mesh.cpp core/scene/Mesh.h core/scene/Material.cpp core/scene/Material.h)

add_executable(${CMAKE_PROJECT_NAME} ${SOURCE_FILES})

# Linking GLFW and OGL
target_link_libraries(${CMAKE_PROJECT_NAME} glfw ${GLFW_LIBRARIES} ${OPENGL_LIBRARY} glm::glm)