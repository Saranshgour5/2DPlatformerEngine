#ifndef GAME_HPP
#define GAME_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_video.h>
#include <iostream>

class Game 
{
public:
	Game ();
	~Game();

	void init(const char* title,int width, int height, bool fullScreen);

	void handleEvents();
	void update();
	bool running() { return isRunning; }
	void render();
	void clean();
	
	static inline bool isRunning { false };
	static SDL_Event event;
	static SDL_Renderer* renderer;
private: 
	int cnt {0};
	SDL_Window* window;
};

#endif
