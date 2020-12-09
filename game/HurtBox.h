#pragma once

#include "Components.h"
#include "SDL.h"


class HurtBox : public Component
{
public:
	TransformComponent* transform;
	SDL_Rect HB;
	int length = 0;
	bool active = false;

	HurtBox()
	{
	
	}
	
	HurtBox(int h, int w)
	{
		HB.h = h;
		HB.w = w;
	}

	void init() override
	{
		if (!entity->hasComponent<TransformComponent>())
		{
			entity->addComponents<TransformComponent>();
		}
		transform = &entity->getComponent<TransformComponent>();

		length = 0;
		active = false;
	}

	void update() override
	{
		if (length > 0)
		{
			active = true;
			length--;
		}
		else
			active = false; 

		HB.x = transform->position.x;
		HB.y = transform->position.y;

		
		
		
		std::cout << length << std::endl;
	}

	
};