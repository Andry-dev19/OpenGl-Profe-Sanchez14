#include "SpriteRenderer.h"
#include <glm/gtc/matrix_transform.hpp>



SpriteRenderer::SpriteRenderer(const Shader& shader)

{

initRenderData();

glm::mat4 projection = glm::ortho(0.0f, 800.0f / 100.0f, 600.0f / 100.0f, 0.0f, -1.0f, 1.0f);

shader.use();

shader.setMatrix4("projection", projection);

}



SpriteRenderer::~SpriteRenderer() {

glDeleteVertexArrays(1, &quadVAO);

}



void SpriteRenderer::setProjection(glm::mat4 proj) {

shader.use();

shader.setMatrix4("projection", proj);

}



void SpriteRenderer::initRenderData() {

GLuint VBO;

float vertices[] = {

0.0f, 1.0f, 0.0f, 1.0f,

1.0f, 0.0f, 1.0f, 0.0f,

0.0f, 0.0f, 0.0f, 0.0f,



0.0f, 1.0f, 0.0f, 1.0f,

1.0f, 1.0f, 1.0f, 1.0f,

1.0f, 0.0f, 1.0f, 0.0f

};



glGenVertexArrays(1, &quadVAO);

glGenBuffers(1, &VBO);



glBindBuffer(GL_ARRAY_BUFFER, VBO);

glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);



glBindVertexArray(quadVAO);

glEnableVertexAttribArray(0);

glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);

glEnableVertexAttribArray(1);

glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));

glBindBuffer(GL_ARRAY_BUFFER, 0);

glBindVertexArray(0);

}



void SpriteRenderer::draw(Texture& texture, glm::vec2 position, glm::vec2 size, glm::vec4 texCoords) {

shader.use();



glm::mat4 model = glm::mat4(1.0f);

model = glm::translate(model, glm::vec3(position, 0.0f));

model = glm::scale(model, glm::vec3(size, 1.0f));



shader.setMatrix4("model", model);

shader.setVec3("spriteColor", glm::vec3(1.0f));



glActiveTexture(GL_TEXTURE0);

texture.bind();



glBindVertexArray(quadVAO);

glDrawArrays(GL_TRIANGLES, 0, 6);

glBindVertexArray(0);

}
