#include <GL/glew.h>
#include <gtc/matrix_transform.hpp>

#include "game.h"

static SpriteRenderer* renderer = NULL;

static void game_init(Game* game, GLuint width, GLuint height)
{
	CHECK_ERROR;
	load_shader("shaders/2d_vertex.glsl", "shaders/2d_fragment.glsl", NULL, "sprite");
	CHECK_ERROR;
	glm::mat4 projection = glm::ortho(0.0f, (GLfloat)width, (GLfloat)height, 0.0f, -1.0f, 1.0f);
	Shader sprite_shader = get_shader("sprite");
	shader_use(&sprite_shader);
	CHECK_ERROR;
	shader_set_integer(&sprite_shader, "image", 0);
	CHECK_ERROR;
	shader_set_matrix4(&sprite_shader, "projection", projection);
	CHECK_ERROR;

	renderer = new_sprite_renderer(sprite_shader);
	CHECK_ERROR;
	load_texture("textures/awesomeface.png", true, "face");
	CHECK_ERROR;
}

static void game_process_input(Game* game, GLfloat dt)
{

}

static void game_update(Game* game, GLfloat dt)
{

}

static void game_render(Game* game)
{
	Texture2D texture = get_texture("face");
	draw_sprite(renderer, &texture, glm::vec2(200, 200), glm::vec2(300, 400), 45.0f, glm::vec3(1.0f, 1.0f, 1.0f));
	//draw_sprite(renderer, &texture, glm::vec2(100, 100), glm::vec2(100, 100), 0.0f, glm::vec3(1.0f, 1.0f, 1.0f));
}