#include "sprite_renderer.h"

static void init_render_data(SpriteRenderer* sr)
{
	GLuint vbo;
	GLfloat vertices[] = {
		// Pos		// Tex
		0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f,

		0.0f, 1.0f, 0.0f, 1.0f, 
		1.0f, 1.0f, 1.0f, 1.0f, 
		1.0f, 0.0f, 1.0f, 0.0f,
	};

	glGenVertexArrays(1, &sr->quad_vao);
	glGenBuffers(1, &vbo);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindVertexArray(sr->quad_vao);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	CHECK_ERROR;
}

static SpriteRenderer* new_sprite_renderer(Shader shader)
{
	SpriteRenderer* result;
	result = (SpriteRenderer*)malloc(sizeof(SpriteRenderer));
	result->shader = shader;
	init_render_data(result);
	return result;
}

static void draw_sprite(SpriteRenderer* sr, Texture2D* texture, glm::vec2 position,
						glm::vec2 size, GLfloat rotate, glm::vec3 color)
{
	shader_use(&sr->shader);
	glm::mat4 model = glm::mat4(1.0);
	model = glm::translate(model, glm::vec3(position, 0.0f));

	model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f));
	model = glm::rotate(model, rotate, glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f));

	model = glm::scale(model, glm::vec3(size, 1.0f));

	shader_set_matrix4(&sr->shader, "model", model);
	shader_set_vector3f(&sr->shader, "spriteColor", color);

	glActiveTexture(GL_TEXTURE0);
	bind_texture(texture);

	// TODO(scott): optimize this to use triangle strip instead
	glBindVertexArray(sr->quad_vao);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
	CHECK_ERROR;
}