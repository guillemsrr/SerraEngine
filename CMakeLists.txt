cmake_minimum_required(VERSION 3.20)
project(SerraEngine)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find packages
find_package(SDL3 CONFIG REQUIRED)
find_package(OpenGL REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)

# Source files
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS src/*.cpp src/*.h src/*.vert src/*.frag src/*.comp)

# ImGui sources (manually specified like in the Makefile)
set(IMGUI_DIR ${CMAKE_CURRENT_SOURCE_DIR}/third_party/imgui)
set(IMGUI_SOURCES
    ${IMGUI_DIR}/imgui.cpp
    ${IMGUI_DIR}/imgui_draw.cpp
    ${IMGUI_DIR}/imgui_tables.cpp
    ${IMGUI_DIR}/imgui_widgets.cpp
    ${IMGUI_DIR}/imgui_demo.cpp
    ${IMGUI_DIR}/backends/imgui_impl_sdl3.cpp
    ${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp
)

# Create library
add_library(SerraEngine STATIC
    ${SOURCES}
    ${IMGUI_SOURCES}
)

# Include paths
target_include_directories(${PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${IMGUI_DIR}
    ${IMGUI_DIR}/backends
)

# Link libraries (vcpkg targets)
target_link_libraries(${PROJECT_NAME}
    PRIVATE
        SDL3::SDL3
        OpenGL::GL
        glad::glad
        glm::glm
)

file(COPY ${CMAKE_SOURCE_DIR}/src/graphics/shaders DESTINATION ${CMAKE_BINARY_DIR})