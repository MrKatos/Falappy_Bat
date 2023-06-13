#include "Menu.h"

Menu::Menu()
{
	this->InitTextures();
	this->InitSprite();
	std::cout << "Menu crated" << std::endl;
}

Menu::~Menu()
{
	std::cout << "Menu deleted" << std::endl;
}

void Menu::InitTextures()
{
	if (!this->BackgroundTex.loadFromFile("textures/menu.png"))
	{
		std::cout << "Couldn't load texture" << "\n";
	}
	else
	{
		this->BackgroundTex.setSmooth(true);
	}
	if (!this->ReplayTex.loadFromFile("textures/replay.png"))
	{
		std::cout << "Couldn't load texture" << "\n";
	}
	else
	{
		this->ReplayTex.setSmooth(true);
	}
	if (!this->PlayTex.loadFromFile("textures/play.png"))
	{
		std::cout << "Couldn't load texture" << "\n";
	}
	else
	{
		this->PlayTex.setSmooth(true);
	}
}

void Menu::InitSprite()
{
	this->Background.setTexture(this->BackgroundTex);
	this->Background.setOrigin(200.f, 300.f);
	this->Background.setPosition(sf::Vector2f(300.f, 300.f));
	this->Background.setScale(0.75f, 0.75f);

	this->Play.setTexture(this->PlayTex);
	//this->Play.setOrigin(26.f, 26.f);
	this->Play.setPosition(sf::Vector2f(330.f, 400.f));
	this->Play.setColor(sf::Color(190, 190, 190, 255));
	this->Play.setScale(2.f, 2.f);

	this->Replay.setTexture(this->ReplayTex);
	//this->Replay.setOrigin(26.f, 26.f);
	this->Replay.setPosition(sf::Vector2f(168.f, 400.f));
	this->Replay.setColor(sf::Color(190, 190, 190, 255));
	this->Replay.setScale(2.f, 2.f);
}

void Menu::InitText()
{
	if (!font.loadFromFile("font.ttf"))
	{
		std::cout << "Can not download font from file" << std::endl;
	}
	else
	{
		this->Score.setFont(font);
		this->Score.setCharacterSize(30);
		this->Score.setFillColor(sf::Color::Cyan);
		this->Score.setPosition(50, 50);
		this->Score.setString("std::to_string(this->score)");

		this->BestScore.setFont(font);
		this->BestScore.setCharacterSize(30);
		this->BestScore.setFillColor(sf::Color::White);
		this->BestScore.setPosition(100, 50);
		this->BestScore.setString(std::to_string(this->bestscore));
	}
}

void Menu::Render(sf::RenderTarget& target)
{
	if (this->ReplayMenu)
	{
		target.draw(this->Background);
		target.draw(this->Replay);
		target.draw(this->Score);
		target.draw(this->BestScore);
	}
	else
	{
		target.draw(this->Background);
		target.draw(this->Replay);
		target.draw(this->Play);
		target.draw(this->Score);
		target.draw(this->BestScore);
	}
}

void Menu::SetScore(int score_arg, int best_score)
{
	this->score = score_arg;
	this->Score.setString(std::to_string(this->score));

	this->bestscore = best_score;
	this->BestScore.setString(std::to_string(this->score));

	std::cout << "score: " << this->score << " " << "Best score: " << this->bestscore << std::endl;
}

void Menu::SetTypeMenu(bool replay_menu)
{
	if (replay_menu)
	{
		this->Replay.setPosition(sf::Vector2f(249.f, 400.f));
		this->ReplayMenu = true;
	}
	else
	{
		this->Replay.setPosition(sf::Vector2f(168.f, 400.f));
		this->ReplayMenu = false;
	}
}

sf::FloatRect Menu::GetPlayBounds()
{
	return this->Play.getGlobalBounds();
}

void Menu::SetPlayColor(sf::Color color)
{
	this->Play.setColor(color);
}

sf::FloatRect Menu::GetReplayBounds()
{
	return this->Replay.getGlobalBounds();
}

void Menu::SetReplayColor(sf::Color color)
{
	this->Replay.setColor(color);
}

