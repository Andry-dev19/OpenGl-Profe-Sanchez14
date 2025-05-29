#ifndef TEXTURE_H

#define TEXTURE_H



#include <string>

#include <glad/glad.h>



class Texture {

public:

 GLuint ID;

int Width, Height;



Texture();

 bool LoadFromFile(const std::string& path);

void bind() const;

void Unbind() const;

void Delete();

 Texture(const char* path); 





};



#endif