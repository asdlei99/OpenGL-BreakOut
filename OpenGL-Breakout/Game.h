#pragma once
#include <GL/glew.h>
#include "SpriteRender.h"
#include "GameLevel.h"

enum GameState {
	GAME_ACTIVE,
	GAME_MENU,
	GAME_WIN
};


class Game {
public:

	SpriteRenderer  *renderer;

	GameState state;
	GLboolean keys[1024];
	GLuint width, height;

	std::vector<GameLevel> levels;
    GLuint                 level;

	Game(GLuint width , GLuint height);
	~Game();

	void Init();
	void ProcessInput(GLuint dt);
	void Update(GLfloat dt);
	void Render();
};

