cmake_minimum_required(VERSION 3.24)
project(learn_opengl)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenGL REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(freeimage CONFIG REQUIRED)


message("===  include_directories ${Stb_INCLUDE_DIR}")
message("=== CMAKE_CURRENT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}")

file(GLOB_RECURSE SOURCE_FILES main.cpp "core/*.cpp" "core/*.h")
add_executable(${CMAKE_PROJECT_NAME} ${SOURCE_FILES})


target_link_libraries(${CMAKE_PROJECT_NAME} freeimage::FreeImage freeimage::FreeImagePlus glm::glm glfw glad::glad ${OPENGL_LIBRARY})

