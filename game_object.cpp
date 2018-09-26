#include "sprite_renderer.h"
#include "game_object.h"

static GameObject* new_game_object(GameObjectType type)
{
	GameObject* result = (GameObject*)malloc(sizeof(GameObject));
	memset(result, 0, sizeof(GameObject));
	result->type = type;
	result->color = Vec3{ 1.0f };
	result->velocity = Vec2{ 0 };
	
	return result;
}

static GameObject* new_ball(Vec2 pos, float radius, Vec2 velocity, Texture2D sprite)
{
	GameObject* result = new_game_object(GameObject_Ball);

	result->position = pos;
	result->size = Vec2{ 2 * radius, 2 * radius };
	result->velocity = velocity;
	result->sprite = sprite;
	result->ball_radius = radius;
	result->ball_stuck = true;

	return result;
}

static void draw_game_object(GameObject* obj, SpriteRenderer* renderer)
{
	draw_sprite(renderer, &obj->sprite, obj->position, obj->size, obj->rotation, obj->color);
}

static Vec2 move_ball(GameObject* ball, float dt, uint32_t window_width)
{
	if (!ball->ball_stuck)
	{
		ball->position += ball->velocity * dt;
		if (ball->position.x <= 0.0f)
		{
			ball->velocity.x = -ball->velocity.x;
			ball->position.x = 0.0f;
		}
		else if (ball->position.x + ball->size.x >= window_width)
		{
			ball->velocity.x = -ball->velocity.x;
			ball->position.x = window_width - ball->size.x;
		}
		if (ball->position.y <= 0)
		{
			ball->velocity.y = -ball->velocity.y;
			ball->position.y = 0;
		}
	}
	return ball->position;
}

static void reset_ball(GameObject* ball, Vec2 position, Vec2 velocity)
{
	ball->position = position;
	ball->velocity = velocity;
	ball->ball_stuck = true;
}

static CollisionResult check_collision(GameObject* a, GameObject* b)
{
	// If one is ball and one is a block, make sure a is the ball
	if (a->type != b->type && b->type == GameObject_Ball)
	{
		GameObject* temp = a;
		a = b;
		b = temp;
	}
	if (a->type == GameObject_Ball)
	{
		Vec2 center = a->position + a->ball_radius;
		Vec2 half_extents = Vec2{ b->size.x / 2.0f, b->size.y / 2.0f };
		Vec2 aabb_center = Vec2{ b->position.x + half_extents.x, b->position.y + half_extents.y };
		Vec2 difference = center - aabb_center;
		Vec2 clamped = glm::clamp(difference, -half_extents, half_extents);
		Vec2 closest = aabb_center + clamped;
		difference = closest - center;
		if (glm::length(difference) <= a->ball_radius)
		{
			return CollisionResult{ true, vector_direction(difference), difference };
		}
		else
		{
			return CollisionResult{ false, DirectionUp, Vec2{0} };
		}
	}
	else
	{
		assert(a->type == GameObject_Brick || a->type == GameObject_Player);
		assert(b->type == GameObject_Brick || b->type == GameObject_Player);
		bool x_axis = a->position.x + a->size.x >= b->position.x &&
			b->position.x + b->size.x >= a->position.x;
		bool y_axis = a->position.y + a->size.y >= b->position.y &&
			b->position.y + b->size.y >= b->position.y;

		// TODO(scott): actually calculate this
		if (x_axis && y_axis)
		{
			return CollisionResult{ true, DirectionUp, Vec2{0} };
		}
		else
		{
			return CollisionResult{ false, DirectionUp, Vec2{ 0 } };
		}
	}
}