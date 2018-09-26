#ifndef _GAME_OBJECT_H_
#define _GAME_OBJECT_H_

#include "bo_math.h"
#include "texture.h"
#include "sprite_renderer.h"

enum GameObjectType {
	GameObject_None,
	GameObject_Brick,
	GameObject_Player,
	GameObject_Ball,
};

struct GameObject {
	GameObjectType type;
	Vec2 position;
	Vec2 size;
	Vec2 velocity;
	Vec3 color;
	float rotation;
	union {
		struct {
			bool block_is_solid;
			bool block_destroyed;
		};
		struct {
			float ball_radius;
			bool ball_stuck;
		};
	};

	Texture2D sprite;
};

GameObject* new_game_object(GameObjectType type);
void draw_game_object(GameObject* obj, SpriteRenderer* renderer);

// Ball specific
GameObject* new_ball(Vec2 pos, float radius, Vec2 velocity, Texture2D sprite);
Vec2 move_ball(GameObject* ball, float dt, uint32_t window_width);
void reset_ball(GameObject* ball, Vec2 position, Vec2 velocity);

bool check_collision(GameObject* a, GameObject* b);


#endif