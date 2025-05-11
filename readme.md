Esta tarea muestra 3 escenas en OpenGL con diferentes figuras y colores. Se puede cambiar de escena con las flechas izquierda y derecha.

tiene que tener descargado:
CMake ≥ 3.20
GLFW
GLAD
Compilador C++:
Windows: MinGW o MSVC
Linux: g++

para compilarlo en Linux (Ubuntu/Debian)

sudo apt update

sudo apt install cmake g++ libglfw3-dev libgl1-mesa-dev

git clone --recurse-submodules https://github.com/Andry-dev19/OpenGl-Profe-Sanchez14.git

cd OpenGl-Profe-Sanchez14

mkdir build && cd build

Nuevas cosas:
El fragment_shader.frag que maneja el color de todas las figuras mediante una variable uniform.

tambien tiene:
Shader.h y elshaders.cpp contienen la clase Shader, que carga, compila y enlaza los shaders.

En el bucle principal (main.cpp), se actualiza el color según la escena actual:


cpp
glm::vec3 figureColors[3] = {
    {1.0f, 0.0f, 0.0f}, Rojo
    {0.0f, 1.0f, 0.0f}, Verde
    {0.0f, 0.0f, 1.0f}  Azul
};


shader.setVec3("uColor", figureColors[currentScene].x, ...);

