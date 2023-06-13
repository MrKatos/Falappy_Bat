#pragma once
#include "RenderEngine.h"

namespace DEAD
{
	enum DeadReason { PIPE, FLOOR, UNKNOWN };
}

class Bat : public RenderEngine
{
public:
	Bat();
	~Bat();
	void SetDeadReason(DEAD::DeadReason reason_arg);
	const DEAD::DeadReason GetDeadReason() const;

	void InitTextures();
	void InitSprite();
	void Render(sf::RenderTarget& target);
	void Update() {};
	const sf::Vector2f GetPosition() const;
	const sf::FloatRect GetGlobalBounds() const;
	void Move(float arg_x, float arg_y);
	void SetTextureRect(sf::IntRect rect);
	void SetPosition(float arg_x, float arg_y);

	friend std::ostream& operator<<(std::ostream& os, const Bat& bat)
	{
		switch (bat.GetDeadReason())
		{
		case DEAD::FLOOR:
			return os << "Bat killed by hitting floor";
			break;
		case DEAD::PIPE:
			return os << "Bat killed by hitting pipe";
			break;
		case DEAD::UNKNOWN:
			return os << "Bat killed with unknown reason";
			break;
		}
	}
private:
	sf::Texture texture; 
	sf::Sprite sprite;
	DEAD::DeadReason reason = DEAD::UNKNOWN;
};

