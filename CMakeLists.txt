cmake_minimum_required(VERSION 3.24)
project(learn_opengl)

set(CMAKE_CXX_STANDARD 17)

add_definitions(-DGLFW_INCLUDE_NONE)

find_package(OpenGL REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(freeimage CONFIG REQUIRED)
find_package(freetype-gl CONFIG REQUIRED)


file(GLOB_RECURSE SOURCE_FILES main.cpp "core/*.h")
add_executable(${CMAKE_PROJECT_NAME} ${SOURCE_FILES})


target_link_libraries(${CMAKE_PROJECT_NAME} freeimage::FreeImage freeimage::FreeImagePlus glm::glm glfw glad::glad freetype-gl ${OPENGL_LIBRARY})
