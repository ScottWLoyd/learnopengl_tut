#include <assert.h>
#include "util.h"

static void init_level(GameLevel* level, std::vector<std::vector<int>> tile_data, uint32_t level_width, uint32_t level_height)
{
	uint32_t height = tile_data.size();
	uint32_t width = tile_data[0].size();
	float unit_width = level_width / (float)width;
	float unit_height = level_height / (float)height;
	for (uint32_t y = 0; y < height; y++)
	{
		for (uint32_t x = 0; x < width; x++)
		{
			if (tile_data[y][x] == 1) // solid tile
			{
				Vec2 pos = Vec2{ unit_width * x, unit_height * y };
				Vec2 size = Vec2{ unit_width, unit_height };
				GameObject* obj = new_game_object(GameObject_Brick);
				obj->position = pos;
				obj->size = size;
				obj->block_is_solid = true;
				obj->sprite = get_texture("block_solid");
				obj->color = Vec3{ 0.8f, 0.8f, 0.7f };
				level->bricks.push_back(*obj);
			}
			else if (tile_data[y][x] > 1)
			{
				Vec3 color = Vec3{ 1.0f };
				if (tile_data[y][x] == 2)
					color = Vec3{ 0.2f ,0.6f, 1.0f };
				else if (tile_data[y][x] == 3)
					color = Vec3{ 0.0f, 0.7f, 0.0f };
				else if (tile_data[y][x] == 4)
					color = Vec3{ 0.8f, 0.8f, 0.4f };
				else if (tile_data[y][x] == 5)
					color = Vec3{ 1.0f, 0.5f, 0.0f };

				Vec2 pos = Vec2{ unit_width * x, unit_height * y };
				Vec2 size = Vec2{ unit_width, unit_height };
				GameObject* obj = new_game_object(GameObject_Brick);
				obj->position = pos;
				obj->size = size;
				obj->color = color;
				obj->sprite = get_texture("block");
				level->bricks.push_back(*obj);
			}
		}
	}
}

void load_game_level(GameLevel* level, int level_id, uint32_t level_width, uint32_t level_height)
{
	assert(level_id >= 0);
	assert(level_id < ARRAY_COUNT(levels));

	level->bricks.clear();

	const char* string = levels[level_id];
	std::vector<std::vector<int>> tile_data;
	std::vector<int> row;
	char* c = (char*)string;
	while (*c)
	{
		if (*c == ' ')
			; // ignore spaces
		else if (*c == '\n') 
		{
			tile_data.push_back(row);
			row.clear();
		}
		else
		{
			int code = *c - '0';
			row.push_back(code);
		}
		c++;
	}
	if (tile_data.size() > 0)
	{
		init_level(level, tile_data, level_width, level_height);
	}
}

void draw_game_level(GameLevel* level, SpriteRenderer* renderer)
{
	for (GameObject& tile : level->bricks)
	{
		if (!tile.block_destroyed)
			draw_game_object(&tile, renderer);
	}
}

bool level_is_completed(GameLevel* level)
{
	for (GameObject& tile : level->bricks)
	{
		if (!tile.block_is_solid && !tile.block_destroyed)
			return false;
	}
	return true;
}