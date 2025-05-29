#include "Texture.h"

#include <glad/glad.h>

#include <stb_image.h>

#include <iostream>



Texture::Texture() : ID(0), Width(0), Height(0) {}

Texture::Texture(const char* path) {

LoadFromFile(std::string(path));

}

bool Texture::LoadFromFile(const std::string& path) {

 glGenTextures(1, &ID);

 glBindTexture(GL_TEXTURE_2D, ID);



glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); 

glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);



 int width, height, nrChannels;

stbi_set_flip_vertically_on_load(true);

unsigned char *data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);

if (data) {

Width = width;

Height = height;

GLenum format = (nrChannels == 4) ? GL_RGBA : GL_RGB;

glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);

glGenerateMipmap(GL_TEXTURE_2D);

} else {
std::cerr << "Failed to load texture: " << path << std::endl;

 return false;

 }

 stbi_image_free(data);

 return true;

}



void Texture::bind() const {

glBindTexture(GL_TEXTURE_2D, ID);

}