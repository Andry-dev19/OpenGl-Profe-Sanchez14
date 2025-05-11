cmake_minimum_required(VERSION 3.20.0 FATAL_ERROR)

project(OpenGLStarter)

set(SOURCE_FILES
    src/main.cpp
    src/elshaders.cpp
)

set(HEADER_FILES
    src/Shader.h
)

add_executable(${PROJECT_NAME} 
    ${HEADER_FILES} 
    ${SOURCE_FILES}
)

find_package(OpenGL REQUIRED)

if (WIN32)
    set(LIBS glfw opengl32 glad)
elseif (UNIX)
    set(LIBS glfw GL glad)
endif ()

set(GLFW_ROOT_DIR external/glfw)
set(GLAD_ROOT_DIR external/glad)

add_subdirectory(${GLFW_ROOT_DIR})
add_subdirectory(${GLAD_ROOT_DIR})

target_include_directories(${PROJECT_NAME} 
    PUBLIC ${GLFW_ROOT_DIR}/include
    PUBLIC ${GLAD_ROOT_DIR}/include/glad
    PUBLIC ${CMAKE_SOURCE_DIR}/external/glm
)

target_link_libraries(${PROJECT_NAME} 
    ${LIBS}
)


file(COPY ${CMAKE_SOURCE_DIR}/shaders DESTINATION ${CMAKE_BINARY_DIR})
