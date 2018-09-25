#include "sprite_renderer.h"
#include "game_object.h"

GameObject* new_game_object(GameObjectType type)
{
	GameObject* result = (GameObject*)malloc(sizeof(GameObject));
	memset(result, 0, sizeof(GameObject));
	result->type = type;
	result->color = Vec3{ 1.0f };
	result->velocity = Vec2{ 0 };

	return result;
}

void draw_game_object(GameObject* obj, SpriteRenderer* renderer)
{
	draw_sprite(renderer, &obj->sprite, obj->position, obj->size, obj->rotation, obj->color);
}