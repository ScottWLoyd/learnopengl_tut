#include <GL/glew.h>
#include <gtc/matrix_transform.hpp>

#include "game.h"
#include "particle_generator.h"

static SpriteRenderer* renderer = NULL;

static Vec2 PLAYER_SIZE = Vec2{ 100, 20 };
static float PLAYER_VELOCITY = 500.0f;
static GameObject* player;

static Vec2 INITIAL_BALL_VELOCITY = Vec2{ 100, -350 };
static float BALL_RADIUS = 12.5f;
static GameObject* ball;

static ParticleGenerator* particles;

static void game_init(Game* game, GLuint width, GLuint height)
{
	game->width = width;
	game->height = height;

	// Load shaders
	load_shader("shaders/2d_vertex.glsl", "shaders/2d_fragment.glsl", NULL, "sprite");
	glm::mat4 projection = glm::ortho(0.0f, (GLfloat)width, (GLfloat)height, 0.0f, -1.0f, 1.0f);
	Shader sprite_shader = get_shader("sprite");
	shader_use(&sprite_shader);
	shader_set_integer(&sprite_shader, "image", 0);
	shader_set_matrix4(&sprite_shader, "projection", projection);

	load_shader("shaders/particle_vertex.glsl", "shaders/particle_fragment.glsl", NULL, "particle");
	

	// Load textures
	renderer = new_sprite_renderer(sprite_shader);
	load_texture("textures/background.jpg", false, "background");
	load_texture("textures/awesomeface.png", true, "face");
	load_texture("textures/ball.png", true, "ball");
	load_texture("textures/block.png", false, "block");
	load_texture("textures/block_solid.png", false, "block_solid");
	load_texture("textures/paddle.png", true, "paddle");
	load_texture("textures/particle.png", true, "particle");

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
	
	Vec2 ball_pos = player_pos + Vec2{ PLAYER_SIZE.x / 2 - BALL_RADIUS, -BALL_RADIUS * 2 };
	ball = new_ball(ball_pos, BALL_RADIUS, INITIAL_BALL_VELOCITY, get_texture("ball"));

	particles = new_particle_generator(get_shader("particle"), get_texture("particle"), 500);

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
			if (player->position.x > 0)
			{
				player->position.x -= velocity;
				if (ball->ball_stuck)
				{
					ball->position.x -= velocity;
				}
			}
			// prevent paddle going one frame off screen
			if (player->position.x < 0)
			{
				player->position.x = 0;
			}
		}
		if (game->keys[GLFW_KEY_D])
		{
			if (player->position.x < game->width - player->size.x - 1)
			{
				player->position.x += velocity;
				if (ball->ball_stuck)
				{
					ball->position.x += velocity;
				}
			}
			// prevent paddle going one frame off screen
			if (player->position.x >= game->width - player->size.x)
			{
				player->position.x = game->width - player->size.x - 1;
			}
		}
		if (game->keys[GLFW_KEY_SPACE])
		{
			ball->ball_stuck = false;
		}
	}
}

static void game_update(Game* game, GLfloat dt)
{
	move_ball(ball, dt, game->width);
	do_collisions(game);
	update_particles(particles, dt, ball, 2, Vec2{ ball->ball_radius / 2 });
}

static void game_render(Game* game)
{
	if (game->state == GAME_ACTIVE)
	{
		Texture2D texture = get_texture("background");
		draw_sprite(renderer, &texture, Vec2{ 0, 0 }, Vec2{ game->width, game->height });

		draw_game_level(&game->levels[game->current_level], renderer);
		draw_game_object(player, renderer);
		draw_particles(particles);
		draw_game_object(ball, renderer);
		//texture = get_texture("face");
		//draw_sprite(renderer, &texture, Vec2{ 0, 0 }, Vec2{ game->width, game->height});
	}
}

static void do_collisions(Game* game)
{
	for (GameObject& box : game->levels[game->current_level].bricks)
	{
		if (!box.block_destroyed)
		{
			CollisionResult collision = check_collision(&box, ball);
			if (collision.collided)
			{
				if (!box.block_is_solid)
				{
					box.block_destroyed = true;
				}
				ScreenDirection dir = collision.direction;
				Vec2 diff_vector = collision.difference;
				if (dir == DirectionLeft || dir == DirectionRight)
				{
					ball->velocity.x = -ball->velocity.x;
					float penetration = ball->ball_radius - fabs(diff_vector.x);
					// TODO(scott): make this precise instead of snapping out of the box
					if (dir == DirectionLeft)
					{
						ball->position.x += penetration;
					}
					else
					{
						assert(dir == DirectionRight);
						ball->position.x -= penetration;
					}
				}
				else
				{
					assert(dir == DirectionUp || dir == DirectionDown);
					ball->velocity.y = -ball->velocity.y;
					float penetration = ball->ball_radius - fabs(diff_vector.y);
					// TODO(scott): make this precise instead of snapping out of the box
					if (dir == DirectionUp)
					{
						ball->position.y -= penetration;
					}
					else
					{
						assert(dir == DirectionDown);
						ball->position.y += penetration;
					}
				}
			}
		}
	}
	// Check paddle collision
	CollisionResult collision = check_collision(ball, player);
	if (!ball->ball_stuck && collision.collided)
	{
		float paddle_center = player->position.x + player->size.x / 2.0f;
		float distance = (ball->position.x + ball->ball_radius) - paddle_center;
		float percentage = distance / (player->size.x / 2.0f);
		float strength = 2.0f;
		Vec2 old_velocity = ball->velocity;
		ball->velocity.x = INITIAL_BALL_VELOCITY.x * percentage * strength;
		ball->velocity.y = -ball->velocity.y;
		ball->velocity = glm::normalize(ball->velocity) * glm::length(old_velocity);
	}
}

static ScreenDirection vector_direction(Vec2 v)
{
	Vec2 compass[] = {
		{0, 1}, // Up
		{-1, 0}, // Left
		{0, -1}, // Down
		{1, 0}, // Right
	};

	float max = 0;
	int best_match = -1;
	for (int i = 0; i < 4; i++)
	{
		float dot = glm::dot(v, compass[i]);
		if (dot > max)
		{
			max = dot;
			best_match = i;
		}
	}
	return (ScreenDirection)best_match;
}