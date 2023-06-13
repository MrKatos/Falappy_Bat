#pragma once
#include "RenderEngine.h"

class Floor : public RenderEngine
{
public:
	Floor(sf::Vector2f position);
	~Floor();
	void InitTextures();
	void InitSprite();
	void Render(sf::RenderTarget& target);
	void Update() {};
	const sf::Vector2f GetPosition() const;
	void Move(float arg_x, float arg_y);

private:
	sf::Vector2f Position;
	sf::Texture texture;
	sf::Sprite sprite;
};

