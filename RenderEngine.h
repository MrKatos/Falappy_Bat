#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class RenderEngine
{
public:
	virtual void InitTextures() = 0;
	virtual void InitSprite() = 0;
	virtual void Render(sf::RenderTarget& target) = 0;
	virtual void Update() = 0;
};

