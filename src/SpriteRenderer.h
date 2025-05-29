// SpriteRenderer.h
#ifndef SPRITE_RENDERER_H
#define SPRITE_RENDERER_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include "Texture.h"
#include "Shader.h"

class SpriteRenderer {
public:
  SpriteRenderer(const Shader& shader);
  ~SpriteRenderer();

  void draw(Texture& texture, glm::vec2 position, glm::vec2 size, glm::vec4 texCoords);
  void setProjection(glm::mat4 proj);

private:
  Shader shader;
  GLuint quadVAO;
  void initRenderData();
};

#endif