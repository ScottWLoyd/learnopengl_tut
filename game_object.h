#ifndef _GAME_OBJECT_H_
#define _GAME_OBJECT_H_

#include "bo_math.h"
#include "texture.h"
#include "sprite_renderer.h"

enum GameObjectType {
	GameObject_None,
	GameObject_Brick,
	GameObject_Player,
};

struct GameObject {
	GameObjectType type;
	Vec2 position;
	Vec2 size;
	Vec2 velocity;
	Vec3 color;
	float rotation;
	bool is_solid;
	bool destroyed;

	Texture2D sprite;
};

GameObject* new_game_object(GameObjectType type);
void draw_game_object(GameObject* obj, SpriteRenderer* renderer);

#endif