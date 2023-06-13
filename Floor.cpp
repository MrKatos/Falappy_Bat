#include "Floor.h"

Floor::Floor(sf::Vector2f position)
{
	this->Position = position;
	this->InitTextures();
	this->InitSprite();
	std::cout << "Floor created" << std::endl;
}

Floor::~Floor()
{
	std::cout << "Floor deleted" << std::endl;
}

void Floor::InitTextures()
{
	if (!this->texture.loadFromFile("textures/floor1.jpg"))
	{
		std::cout << "Couldn't load texture" << "\n";
	}
	else
	{
		this->texture.setSmooth(true);
	}
}

void Floor::InitSprite()
{
	this->sprite.setTexture(this->texture);
	this->sprite.setPosition(this->Position);
}

void Floor::Render(sf::RenderTarget& target)
{
	target.draw(this->sprite);
}

const sf::Vector2f Floor::GetPosition() const
{
	return this->sprite.getPosition();
}

void Floor::Move(float arg_x, float arg_y)
{
	this->sprite.move(arg_x, arg_y);
}
