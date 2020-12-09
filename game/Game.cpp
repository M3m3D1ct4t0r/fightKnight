#include "Game.h"
#include "TextureManager.h"
#include "Map.h"
#include "ECS.h"
#include "Components.h"
#include "Vector2D.h"
#include "Collision.h"
#include "GameObject.h"



SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

std::vector<ColliderComponent*> Game::colliders;

bool Game::isRunning = false;



Manager manager;
auto& player(manager.addEntity());

auto& enemy(manager.addEntity());



const char* mapfile = "assets/tiles2.png";

enum groupLabels : std::size_t
{
	groupMap,
	groupPlayers,
	groupEnimies,
	groupColliders,
	groupPlaforms,
};

auto& tiles(manager.getGroup(groupMap));
auto& players(manager.getGroup(groupPlayers));
auto& enemies(manager.getGroup(groupEnimies));
auto& colliders(manager.getGroup(groupColliders));
auto& platforms(manager.getGroup(groupPlaforms));

Game::Game()
{}
Game::~Game()
{}

void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
	int flags = 0;
	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		std::cout << "subsystems initiaized" << std::endl;


		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		if (window)
		{
			std::cout << "window created..." << std::endl;
		}

		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			std::cout << "renderererer created..." << std::endl;
		}

		isRunning = true;
	}
	else {
		isRunning = false;
	}
	

	AddTile(0, 0, 0, 0);
	AddPlatform(0, 0, 1, 10);
	AddPlatform(0, 0, 2, 10);
	AddPlatform(0, 0, 3, 10);
	AddPlatform(0, 0, 4, 10);
	AddPlatform(0, 0, 5, 10);
	AddPlatform(0, 0, 6, 10);
	AddPlatform(0, 0, 7, 10);
	AddPlatform(0, 0, 8, 10);
	AddPlatform(0, 0, 9, 10);
	AddPlatform(0, 0, 10, 10);
	AddPlatform(0, 0, 11, 10);
	AddPlatform(0, 0, 12, 10);
	AddPlatform(0, 0, 13, 10);
	
	
	enemy.addComponents<TransformComponent>(550.0f, 450.0f, 32, 32, 2);
	enemy.addComponents<ColliderComponent>("enemy");
	enemy.addComponents<SpriteComponent>("assets/boi_multi.png");
	enemy.addGroup(groupEnimies);
	
	player.addComponents<TransformComponent>(400.0f, 150.0f,64,64,2);
//	player.addComponents<SpriteComponent>("assets/boi_multi.png",true);
	player.addComponents<SpriteComponent>("assets/knite.png",true);
	player.addComponents<KeyboardController>();
	player.addComponents<ColliderComponent>("player");
	player.addComponents<HurtBox>(32, 64);
	player.addGroup(groupPlayers);



	
}


void Game::handleEvents()
{
	
	SDL_PollEvent(&event);
	switch (event.type) {
	case SDL_QUIT:
		isRunning = false;
		break;

	default:
		break;
	}

}
bool canJump = false;

void Game::update()
{
	//if (player.getComponent<TransformComponent>().acceleration.x > 0) player.getComponent<TransformComponent>().acceleration.x--;
	//if (player.getComponent<TransformComponent>().acceleration.x < 0) player.getComponent<TransformComponent>().acceleration.x++;

	if (player.getComponent<TransformComponent>().position.x < 0) player.getComponent<TransformComponent>().position.x = 1;

	if (player.getComponent<TransformComponent>().position.x > 735) player.getComponent<TransformComponent>().position.x = 734;

	bool inAir = true;
	for (auto p : platforms)
	{
		if (Collision::AABB(p->getComponent<ColliderComponent>(), player.getComponent<ColliderComponent>()))
		{
			
			if (player.getComponent<TransformComponent>().position.y = p->getComponent<TransformComponent>().position.y)
			{
				inAir = false;
				player.getComponent<TransformComponent>().velocity.y = 0;
				player.getComponent<TransformComponent>().position.y = p->getComponent<TransformComponent>().position.y - 128;
			}

		
			//if that particular platform left right ext... 
		}
		
	}
	
	if (inAir)
	{
		player.getComponent<TransformComponent>().acceleration.y = .8;         // <--- this number is effctivily the charector weight...
		//std::cout << "fallin" << std::endl;
		canJump = false;
	}
	else
	{
		player.getComponent<TransformComponent>().acceleration.y = 0;
		//std::cout << "standin" << std::endl;
		canJump = true;
	}




	if (enemy.hasComponent<ColliderComponent>())
	{
		if (Collision::AABB(enemy.getComponent<ColliderComponent>(), player.getComponent<HurtBox>().HB) && player.getComponent<HurtBox>().active)
		{
			std::cout << "hit landed" << std::endl;
		}
	}


	manager.refresh();
	manager.update();
}



void Game::render()
{
	SDL_RenderClear(renderer);
	
	for (auto& t : tiles)
	{
		t->draw();
	}
	
	for (auto& p : players)
	{
		p->draw();
	}
	
	for (auto& e : enemies)
	{
		e->draw();
	}
	
	/*for (auto& c : colliders)
	{
		c->draw();
	}*/

	for (auto& p : platforms)
	{
		p->draw();
	}
	SDL_RenderPresent(renderer);
	
}

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();

	std::cout << "game cleaned" << std::endl;
}

void Game::AddTile(int srcX, int srcY, int xpos, int ypos) 
{
	auto& tile(manager.addEntity());
	tile.addComponents<TileComponent>(srcX, srcY, xpos, ypos,"assets/placeHolder.png"); //////
	tile.addGroup(groupMap);
}

void Game::AddPlatform(int srcX, int srcY, int xpos, int ypos)
{
	auto& platform(manager.addEntity());
//	platform.addComponents<TransformComponent>(x, y, height, width, scale );
	
	ypos--;
	xpos--;
	platform.addComponents<TransformComponent>(xpos*64.0f, ypos*64.0f, 32, 32, 2);
	platform.addComponents<SpriteComponent>("assets/tiles.png");
	platform.addComponents<ColliderComponent>("platform");
	platform.addGroup(groupPlaforms);
}

bool Game::jumpPoss()
{
	return canJump;
}

void Game::manageAttack(int SUF, int HF, int EF)
{
	player.getComponent<HurtBox>().length = 60;
	
	/*if(enemy.hasComponent<TransformComponent>());
		enemy.destroy();*/
}