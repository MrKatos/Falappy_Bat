#include "Background.h"

Background::Background()
{
	this->InitTextures();
	this->InitSprite();
	std::cout << "Backgound created" << std::endl;
}

Background::~Background()
{
	std::cout << "Backgound created" << std::endl;
}

void Background::InitTextures()
{
	if (!this->texture.loadFromFile("textures/background1.jpg"))
	{
		std::cout << "Couldn't load texture" << "\n";
	}
	else
	{
		this->texture.setSmooth(true);
	}
}

void Background::InitSprite()
{
	this->sprite.setTexture(texture);
	this->sprite.setPosition(sf::Vector2f(300.f, 450.f));
	this->sprite.setOrigin(sf::Vector2f(450.f, 400.f));
	this->sprite.setScale(sf::Vector2f(1.6f, 1.6f));
}

void Background::Render(sf::RenderTarget& target)
{
	target.draw(this->sprite);
}
