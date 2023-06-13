#include "Pipe.h"

Pipe::Pipe(sf::Vector2f position_arg, float angle_arg)
{
	this->Angle = angle_arg;
	this->Position = position_arg;
	this->InitTextures();
	this->InitSprite();
	std::cout << "Pipe created" << std::endl;
}

Pipe::~Pipe()
{
	std::cout << "Pipe deleted" << std::endl;
}

void Pipe::InitTextures()
{
	if (!this->texture.loadFromFile("textures/pike.jpg"))
	{
		std::cout << "Couldn't load texture" << "\n";
	}
	else
	{
		this->texture.setSmooth(true);
	}
}

void Pipe::InitSprite()
{
	this->sprite.setTexture(this->texture);
	this->sprite.setPosition(this->Position);
	this->sprite.setRotation(this->Angle);
	this->sprite.setScale(sf::Vector2f(0.5f, 1.f));
	this->sprite.setOrigin(sf::Vector2f(125.f, 160.f));
}

void Pipe::Render(sf::RenderTarget& target)
{
	target.draw(this->sprite);
}

const sf::Vector2f Pipe::GetPosition() const
{
	return this->sprite.getPosition();
}

const sf::FloatRect Pipe::GetGlobalBounds() const
{
	return this->sprite.getGlobalBounds();
}

void Pipe::Move(float arg_x, float arg_y)
{
	this->sprite.move(arg_x, arg_y);
}
