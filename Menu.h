#pragma once
#include "RenderEngine.h"

class Menu : public RenderEngine
{
public:
	Menu();
	~Menu();
	void InitTextures() override;
	void InitSprite() override;
	void InitText();
	void Render(sf::RenderTarget& target) override;
	void Update() {};
	void SetScore(int score_arg, int best_score);
	void SetTypeMenu(bool replay_menu);
	sf::FloatRect GetPlayBounds();
	void SetPlayColor(sf::Color color);
	sf::FloatRect GetReplayBounds();
	void SetReplayColor(sf::Color color);

private:
	bool ReplayMenu = false;

	sf::Texture BackgroundTex;
	sf::Sprite Background;

	sf::Texture ReplayTex;
	sf::Sprite Replay;

	sf::Texture PlayTex;
	sf::Sprite Play;

	sf::Font font;
	sf::Text Score;
	int score = 0;
	sf::Text BestScore;
	int bestscore = 0;
};

