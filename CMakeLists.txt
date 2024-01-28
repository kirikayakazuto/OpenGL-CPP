cmake_minimum_required(VERSION 3.24)
project(learn_opengl)

set(CMAKE_CXX_STANDARD 17)

add_definitions(-DGLFW_INCLUDE_NONE)

find_package(OpenGL REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(freeimage CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)
find_package(nanovg CONFIG REQUIRED)
find_package(assimp CONFIG REQUIRED)

find_path(TINYGLTF_INCLUDE_DIRS "tiny_gltf.h")
include_directories(${CMAKE_PROJECT_NAME} PRIVATE ${TINYGLTF_INCLUDE_DIRS})

file(GLOB_RECURSE SOURCE_FILES main.cpp "core/*.h")
add_executable(${CMAKE_PROJECT_NAME} ${SOURCE_FILES})

target_link_libraries(${CMAKE_PROJECT_NAME} freeimage::FreeImage freeimage::FreeImagePlus glm::glm glfw glad::glad nlohmann_json::nlohmann_json nanovg::nanovg assimp::assimp ${OPENGL_LIBRARY})
