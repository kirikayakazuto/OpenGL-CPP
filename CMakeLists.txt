cmake_minimum_required(VERSION 3.24)
project(learn_opengl)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenGL REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(freeimage CONFIG REQUIRED)


file(GLOB_RECURSE SOURCE_FILES main.cpp "core/*.cpp" "core/*.h")
add_executable(${CMAKE_PROJECT_NAME} ${SOURCE_FILES}
        core/components/RenderComponent.cpp
        core/components/RenderComponent.h
        core/components/BaseComponent.cpp
        core/components/BaseComponent.h
        core/components/Sprite.cpp
        core/components/Sprite.h
        core/components/Shape.cpp
        core/components/Shape.h)


target_link_libraries(${CMAKE_PROJECT_NAME} freeimage::FreeImage freeimage::FreeImagePlus glm::glm glfw glad::glad ${OPENGL_LIBRARY})

