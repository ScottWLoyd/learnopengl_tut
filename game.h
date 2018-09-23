#ifndef _GAME_H_
#define _GAME_H_

enum GameState {
	GAME_ACTIVE,
	GAME_MENU,
	GAME_WIN,
};

struct Game {
	GameState state;
	GLboolean keys[1024];
	GLuint width, height;
};

static void game_init(Game* game, GLuint width, GLuint height);
static void game_process_input(Game* game, GLfloat dt);
static void game_update(Game* game, GLfloat dt);
static void game_render(Game* game);

#endif