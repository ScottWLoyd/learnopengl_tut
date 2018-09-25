#ifndef _GAME_LEVEL_H_
#define _GAME_LEVEL_H_

#include <vector>

#include "game_object.h"
#include "sprite_renderer.h"

struct GameLevel {
	std::vector<GameObject> bricks;
};

const char* levels[] = {
	"5 5 5 5 5 5 5 5 5 5 5 5 5 5 5\n"
	"5 5 5 5 5 5 5 5 5 5 5 5 5 5 5\n"
	"4 4 4 4 4 0 0 0 0 0 4 4 4 4 4\n"
	"4 1 4 1 4 0 0 1 0 0 4 1 4 1 4\n"
	"3 3 3 3 3 0 0 0 0 0 3 3 3 3 3\n"
	"3 3 1 3 3 3 3 3 3 3 3 3 1 3 3\n"
	"2 2 2 2 2 2 2 2 2 2 2 2 2 2 2\n"
	"2 2 2 2 2 2 2 2 2 2 2 2 2 2 2\n",

	"1 1 1 1 1 1 1 1 1 1 1 1 1 1 1\n" 	 
	"1 0 5 5 0 5 5 0 5 5 0 5 5 0 1\n"
	"1 5 5 5 5 5 5 5 5 5 5 5 5 5 1\n"
	"1 0 3 3 0 3 3 0 3 3 0 3 3 0 1\n"
	"1 3 3 3 3 3 3 3 3 3 3 3 3 3 1\n"
	"1 0 2 2 0 2 2 0 2 2 0 2 2 0 1\n"
	"1 2 2 2 2 2 2 2 2 2 2 2 2 2 1\n"
	"1 0 1 1 0 1 1 0 1 1 0 1 1 0 1",

	"0 0 0 0 0 0 0 0 0 0 0 0 0\n"
	"0 0 2 0 0 0 0 0 0 0 2 0 0\n"
	"0 0 0 2 0 0 0 0 0 2 0 0 0\n"
	"0 0 0 5 5 5 5 5 5 5 0 0 0\n"
	"0 0 5 5 0 5 5 5 0 5 5 0 0\n"
	"0 5 5 5 5 5 5 5 5 5 5 5 0\n"
	"0 3 0 1 1 1 1 1 1 1 0 3 0\n"
	"0 3 0 3 0 0 0 0 0 3 0 3 0\n"
	"0 0 0 0 4 4 0 4 4 0 0 0 0",

	"1 2 1 2 1 2 1 2 1 2 1 2 1\n"
	"2 2 2 2 2 2 2 2 2 2 2 2 2\n"
	"2 1 3 1 4 1 5 1 4 1 3 1 2\n"
	"2 3 3 4 4 5 5 5 4 4 3 3 2\n"
	"2 1 3 1 4 1 5 1 4 1 3 1 2\n"
	"2 2 3 3 4 4 5 4 4 3 3 2 2",
};

void load_game_level(GameLevel* level, int level_id, uint32_t level_width, uint32_t level_height);
void draw_game_level(GameLevel* level, SpriteRenderer* renderer);
bool level_is_completed(GameLevel* level);

#endif
