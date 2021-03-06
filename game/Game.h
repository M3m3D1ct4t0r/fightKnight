#pragma once

#ifndef Game_hpp
#define Game_hpp
#include "SDL.h"
#include "iostream"
#include "SDL_image.h"
#include <vector>


class ColliderComponent;

class Game {
public:
	Game();
	~Game();

	void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
	bool running() { return isRunning; }
	void handleEvents();
	void update();
	void render();
	void clean();
	static void AddTile( int srcX, int srcY, int xpos, int ypos);
	static void AddPlatform( int srcX, int srcY, int xpos, int ypos);
	
	static bool jumpPoss();
	static void manageAttack(int SUF, int HF, int EF);

	static SDL_Renderer* renderer;
	static SDL_Event event;
	static std::vector<ColliderComponent*> colliders; 
	static bool isRunning;

	
	

private:
	//int count = 0;
	SDL_Window *window;
};

#endif /*  Game_hpp   */