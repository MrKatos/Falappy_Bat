#pragma once

#include "RenderEngine.h"

class Background : public RenderEngine
{
public:
	Background();
	~Background();

	void InitTextures();
	void InitSprite();
	void Render(sf::RenderTarget& target);
	void Update() {};

private:
	sf::Texture texture;
	sf::Sprite sprite;
};

