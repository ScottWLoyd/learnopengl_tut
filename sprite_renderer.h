#ifndef _SPRITE_RENDERER_H_
#define _SPRITE_RENDERER_H_

#include <GL/glew.h>
#include <glm.hpp>

#include "shader.h"
#include "texture.h"

struct SpriteRenderer {
	Shader shader;
	GLuint quad_vao;
};

static SpriteRenderer* new_sprite_renderer(Shader shader);

static void draw_sprite(SpriteRenderer* sr, Texture2D* texture, glm::vec2 position,
	glm::vec2 size = glm::vec2(10, 10), GLfloat rotate = 0.0f,
	glm::vec3 color = glm::vec3(1.0f));

#endif