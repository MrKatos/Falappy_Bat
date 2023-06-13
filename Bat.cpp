#include "Bat.h"

Bat::Bat()
{
	this->InitTextures();
	this->InitSprite();
	std::cout << "Bat created" << std::endl;
}

Bat::~Bat()
{
	std::cout << "Bat deleted" << std::endl;
}

void Bat::InitTextures()
{
	if (!this->texture.loadFromFile("textures/bat.png"))
	{
		std::cout << "Couldn't load texture" << "\n";
	}
	else
	{
		this->texture.setSmooth(true);
	}
}

void Bat::InitSprite()
{
	this->sprite.setTexture(texture);
	this->sprite.setPosition(sf::Vector2f(300.f, 300.f));
	this->sprite.setOrigin(sf::Vector2f(101.f, 81.f));
	this->sprite.setTextureRect(sf::IntRect(0.f, 0.f, 184.f, 87.f));
}

void Bat::Render(sf::RenderTarget& target)
{
	target.draw(this->sprite);
}

const sf::Vector2f Bat::GetPosition() const
{
	return this->sprite.getPosition();
}

const sf::FloatRect Bat::GetGlobalBounds() const
{
	return this->sprite.getGlobalBounds();
}

void Bat::Move(float arg_x, float arg_y)
{
	this->sprite.move(arg_x, arg_y);
}

void Bat::SetTextureRect(sf::IntRect rect)
{
	this->sprite.setTextureRect(rect);
}

void Bat::SetPosition(float arg_x, float arg_y)
{
	this->sprite.setPosition(arg_x, arg_y);
}

void Bat::SetDeadReason(DEAD::DeadReason reason_arg)
{
	this->reason = reason_arg;
}

const DEAD::DeadReason Bat::GetDeadReason() const
{
	return this->reason;
}


