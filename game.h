#ifndef _GAME_H_
#define _GAME_H_

#include <vector>

#include "game_level.h"

enum GameState {
	GAME_ACTIVE,
	GAME_MENU,
	GAME_WIN,
};

#define MAX_LEVELS 5

struct Game {
	GameState state;
	GLboolean keys[1024];
	GLuint width, height;
	GameLevel levels[MAX_LEVELS];
	uint32_t num_levels;
	uint32_t current_level;
};

static void game_init(Game* game, GLuint width, GLuint height);
static void game_process_input(Game* game, GLfloat dt);
static void game_update(Game* game, GLfloat dt);
static void game_render(Game* game);

#endif