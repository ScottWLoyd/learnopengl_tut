#include <GL/glew.h>
#include <gtc/matrix_transform.hpp>

#include "game.h"

static SpriteRenderer* renderer = NULL;
static Vec2 PLAYER_SIZE = Vec2{ 100, 20 };
static float PLAYER_VELOCITY = 500.0f;

static GameObject* player;

static void game_init(Game* game, GLuint width, GLuint height)
{
	game->width = width;
	game->height = height;

	load_shader("shaders/2d_vertex.glsl", "shaders/2d_fragment.glsl", NULL, "sprite");
	glm::mat4 projection = glm::ortho(0.0f, (GLfloat)width, (GLfloat)height, 0.0f, -1.0f, 1.0f);
	Shader sprite_shader = get_shader("sprite");
	shader_use(&sprite_shader);
	shader_set_integer(&sprite_shader, "image", 0);
	shader_set_matrix4(&sprite_shader, "projection", projection);

	// Load textures
	renderer = new_sprite_renderer(sprite_shader);
	load_texture("textures/background.jpg", false, "background");
	load_texture("textures/awesomeface.png", true, "face");
	load_texture("textures/block.png", false, "block");
	load_texture("textures/block_solid.png", false, "block_solid");
	load_texture("textures/paddle.png", true, "paddle");
	// Load levels
	load_game_level(&game->levels[0], 0, width, (uint32_t)(height * 0.5f));
	game->num_levels++;
	load_game_level(&game->levels[1], 0, width, (uint32_t)(height * 0.5f));
	game->num_levels++;
	load_game_level(&game->levels[2], 0, width, (uint32_t)(height * 0.5f));
	game->num_levels++;
	load_game_level(&game->levels[3], 0, width, (uint32_t)(height * 0.5f));
	game->num_levels++;

	Vec2 player_pos = Vec2{
		game->width / 2 - PLAYER_SIZE.x / 2,
		game->height - PLAYER_SIZE.y
	};
	player = new_game_object(GameObject_Player);
	player->position = player_pos;
	player->size = PLAYER_SIZE;
	player->sprite = get_texture("paddle");

	game->current_level = 0;

	CHECK_ERROR;
}

static void game_process_input(Game* game, GLfloat dt)
{
	if (game->state == GAME_ACTIVE)
	{
		float velocity = PLAYER_VELOCITY * dt;
		if (game->keys[GLFW_KEY_A])
		{
			if (player->position.x >= 0)
				player->position.x -= velocity;
			if (player->position.x < 0)
				player->position.x = 0;
		}
		if (game->keys[GLFW_KEY_D])
		{
			if (player->position.x < game->width - player->size.x)
				player->position.x += velocity;
			if (player->position.x >= game->width - player->size.x)
				player->position.x = game->width - player->size.x - 1;
		}
	}
}

static void game_update(Game* game, GLfloat dt)
{

}

static void game_render(Game* game)
{
	if (game->state == GAME_ACTIVE)
	{
		Texture2D texture = get_texture("background");
		draw_sprite(renderer, &texture, Vec2{ 0, 0 }, Vec2{ game->width, game->height });

		draw_game_level(&game->levels[game->current_level], renderer);
		draw_game_object(player, renderer);
		//texture = get_texture("face");
		//draw_sprite(renderer, &texture, Vec2{ 0, 0 }, Vec2{ game->width, game->height});
	}
}