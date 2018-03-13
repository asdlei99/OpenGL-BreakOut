#pragma once
#include <GL/glew.h>

enum GameState {
	GAME_ACTIVE,
	GAME_MENU,
	GAME_WIN
};


class Game {
public:

	GameState state;
	GLboolean keys[1024];
	GLuint width, height;

	Game(GLuint width , GLuint height);
	~Game();

	void Init();
	void ProcessInput(GLuint dt);
	void Update(GLfloat dt);
	void Render();
};
