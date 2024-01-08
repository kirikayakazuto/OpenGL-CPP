cmake_minimum_required(VERSION 3.24)
project(learn_opengl)

set(CMAKE_CXX_STANDARD 17)

# 设置 vcpkg 的工具链文件路径
set(CMAKE_TOOLCHAIN_FILE /Users/denglang/.vcpkg-clion/vcpkg/scripts/buildsystems/vcpkg.cmake)
set(VCPKG_FILE /Users/denglang/.vcpkg-clion/vcpkg/packages)

find_package(OpenGL REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(Stb REQUIRED)
# include_directories(${Stb_INCLUDE_DIR})
target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC ${Stb_INCLUDE_DIR})

# set(SOURCE_FILES main.cpp ${SOURCE_FILES})
file(GLOB SOURCE_FILES main.cpp "core/renderer/*.cpp" "core/renderer/*.h" "core/scene/*.cpp" "core/scene/*.h")
add_executable(${CMAKE_PROJECT_NAME} ${SOURCE_FILES})


target_link_libraries(${CMAKE_PROJECT_NAME} glm::glm glfw glad::glad ${OPENGL_LIBRARY})

