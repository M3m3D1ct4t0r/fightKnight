#pragma once

#include "ECS.h"
#include "SDL.h"



class TileComponent : public Component
{
public:
	
	SDL_Texture* texture;
	SDL_Rect srcRect, destRect;

	TileComponent() = default;
	
	~TileComponent()
	{
		SDL_DestroyTexture(texture);
	}

	TileComponent(int srcX, int srcY, int xpos, int ypos, const char* path)
	{
		texture = textureManager::LoadTexture(path);

		srcRect.x = srcX;
		srcRect.y = srcY;
		srcRect.w = 800;
		srcRect.h = 640;

		destRect.x = xpos;
		destRect.y = ypos;
		destRect.w = 800;
		destRect.h = 640;

	}


	void draw() override
	{
		textureManager::Draw(texture, srcRect, destRect);
	}
	
};
