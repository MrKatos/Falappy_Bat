#pragma once
#include "RenderEngine.h"

class Pipe : /*public sf::Sprite, */public RenderEngine
{
public:
	Pipe(sf::Vector2f position_arg, float angle_arg);
	~Pipe();
	void InitTextures();
	void InitSprite();
	void Render(sf::RenderTarget& target);
	void Update() {};
	const sf::Vector2f GetPosition() const;
	const sf::FloatRect GetGlobalBounds() const;
	void Move(float arg_x, float arg_y);

private:
	sf::Texture texture;
	sf::Sprite sprite;
	sf::Vector2f Position;
	float Angle;
};
