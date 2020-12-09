#pragma once

#include "Game.h"
#include "ECS.h"
#include "Components.h"

class KeyboardController : public Component
{

public:
	TransformComponent* transform;
	SpriteComponent* sprite;
	void init() override
	{
		transform = &entity->getComponent<TransformComponent>();
		sprite = &entity->getComponent<SpriteComponent>();
	}


	void update() override
	{
		/*if (Game::jumpPoss() == true)
		{
			std::cout << "can jump" << std::endl;
		}
		else
		{
			std::cout << "NO jump" << std::endl;
		}*/
	



		if (Game::event.type == SDL_KEYUP)
		{
			switch (Game::event.key.keysym.sym)
			{
			case SDLK_ESCAPE:
				Game::isRunning = false;
				break;
			/*case SDLK_SPACE:
				Game::manageAttack(0,0,0);
				break;*/
			default:
				break;
			}
		}

		const Uint8* keyState = SDL_GetKeyboardState(NULL);

		if (keyState[SDL_SCANCODE_D])
		{
			sprite->Play("walkd");
			transform->velocity.x = 4;
		}
		else if (keyState[SDL_SCANCODE_A])
		{
			sprite->Play("walka");
			transform->velocity.x = -4;
		}
		else
		{
			sprite->Play("idle");
			transform->velocity.x = 0;
		}
		


		if (keyState[SDL_SCANCODE_W])
		{			
			if (Game::jumpPoss() == true)
			{
				sprite->Play("walkw");
				transform->position.y--;
				transform->velocity.y = -15;     //   <--- this # is effectivily the strength of his jump...
			}
		}
		else if (keyState[SDL_SCANCODE_S])
		{
			sprite->Play("walks");
			transform->velocity.y = 1;
		}
		else
		{
			//sprite->Play("idle");
			//transform->velocity.y = 0;
		}

		if (keyState[SDL_SCANCODE_SPACE])
		{
			Game::manageAttack(0, 0, 0);
		}
	}
};