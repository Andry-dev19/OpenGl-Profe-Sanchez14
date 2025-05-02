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

cmake ..

cmake --build .

./OpenGLStarter

